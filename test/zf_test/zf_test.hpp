#pragma once

#include <string>
#include <list>

#if !defined(STRINGIFY) && !defined(_STRINGIFY)
#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)
#endif

namespace zf_test
{
	extern inline std::string strformat(const char *const fmt, ...)
	{
		char stack_buf[256];
		std::unique_ptr<char[]> heap_buf;
		char *buf = stack_buf;
		int buf_sz = sizeof(stack_buf);

		va_list ap;
		int len;
		for(;;)
		{
			va_start(ap, fmt);
			len = std::vsnprintf(buf, buf_sz, fmt, ap);
			va_end(ap);
			if (buf_sz > len)
			{
				break;
			}
			buf_sz = len + 1;
			heap_buf.reset(new char[buf_sz]);
			buf = heap_buf.get();
		}
		return 0 < len? std::string(buf, len): std::string();
	}

	template <typename T>
	extern inline std::string to_hex(const T &v)
	{
		const char hex[] = "0123456789abcdef";
		const unsigned char *const b = (const unsigned char *)&v;
		const unsigned char *const e = b + sizeof(v);
		std::string str(2 * sizeof(v), 0);
		char *s = &str[0];
		for (const unsigned char *p = b; e != p; ++p)
		{
			*s++ = hex[0x0f & (*p  >> 4)];
			*s++ = hex[0x0f & *p];
		}
		return str;
	}

	template <typename T>
	extern inline std::string to_string(const T &v)
	{
		return to_hex(v);
	}

	extern inline std::string to_string(const std::string &v)
	{
		return v;
	}

	extern inline std::string to_string(const char *const v)
	{
		return std::string(v);
	}

	extern inline std::pair<size_t, size_t> eolpos(const char *const s)
	{
		for (size_t i = 0, n;; i = n)
		{
			n = i + 1;
			switch (s[i])
			{
			case 0:
				return std::make_pair(i, i);
			case '\n':
				return std::make_pair(i, n);
			case '\r':
				if ('\n' == s[n])
				{
					++n;
				}
				return std::make_pair(i, n);
			default:
				break;
			}
		}
	}

	class test_result
	{
	public:
		const std::string message;

		test_result(const char *const message):
			message(message), m_max_name_len(0)
		{}

		void add(const char *const name, const char *const value)
		{
			pair_t p(name, value);
			if (m_max_name_len < p.first.size())
			{
				m_max_name_len = p.first.size();
			}
			m_pairs.push_back(std::move(p));
		}

		void add(const test_result &other)
		{
			for (std::list<pair_t>::const_iterator p = other.m_pairs.begin();
				 other.m_pairs.end() != p; ++p)
			{
				add(p->first.c_str(), p->second.c_str());
			}
		}

		void fprint(FILE *const f, const char *const indent) const
		{
			for (std::list<pair_t>::const_iterator p = m_pairs.begin();
				 m_pairs.end() != p; ++p)
			{
				const std::string pad1(m_max_name_len + 1 - p->first.size(), ' ');
				const char *lines = p->second.c_str();
				std::pair<size_t, size_t> eol = eolpos(lines);
				std::string result = strformat("%s%s:%s", indent, p->first.c_str(), pad1.c_str());
				const unsigned pad2_len = result.size();
				result.append(lines, eol.second);
				lines += eol.second;
				while (0 != *lines)
				{
					eol = eolpos(lines);
					result.append(pad2_len, ' ');
					result.append(lines, eol.second);
					lines += eol.second;
				}
				result.append("\n");
				fputs(result.c_str(), f);
			}
		}
	private:
		typedef std::pair<std::string, std::string> pair_t;
		std::list<pair_t> m_pairs;
		unsigned m_max_name_len;
	};

	class test_verify_exception
	{
	public:
		const std::string file;
		const unsigned line;
		const test_result result;

		test_verify_exception(const char *const file, const unsigned line,
							  test_result &result):
			file(file), line(line), result(result)
		{}
	};

	class test_runner
	{
	public:
		unsigned error_count;
		unsigned verbosity;
		const char *suite_name;
		const char *test_name;

		test_runner(const unsigned argc, const char *const argv[]):
			error_count(0),
			verbosity(0),
			suite_name(nullptr),
			test_name(nullptr)
		{
			(void)argc; (void)argv;
		}
	};
}

#define TEST_VERIFY_THROW(result) \
	do { \
		throw zf_test::test_verify_exception(__FILE__, __LINE__, std::move(result)); \
	} \
	while (false)

#define TEST_VERIFY_TRUE(v) \
	do { \
		const bool t = v; \
		if (!t) \
		{ \
			zf_test::test_result result("not true"); \
			result.add("false", STRINGIFY(v));  \
			TEST_VERIFY_THROW(result); \
		} \
	} \
	while (false)

#define TEST_VERIFY_FALSE(v) \
	do { \
		const bool t = v; \
		if (t) \
		{ \
			zf_test::test_result result("not false"); \
			result.add("true", STRINGIFY(v));  \
			TEST_VERIFY_THROW(result); \
		} \
	} \
	while (false)

#define TEST_VERIFY_IN_EPSILON(a, b, eps) \
	do { \
		const auto va = a; \
		const auto vb = b; \
		const auto veps = eps; \
		if (veps <= std::abs(va - vb)) \
		{ \
			zf_test::test_result result("not in epsilon neighborhood"); \
			result.add("left", strformat("%s (%s)", zf_test::to_string(va).c_str(), STRINGIFY(a)).c_str()); \
			result.add("right", strformat("%s (%s)", zf_test::to_string(vb).c_str(), STRINGIFY(b)).c_str()); \
			result.add("epsilon", strformat("%s (%s)", zf_test::to_string(veps).c_str(), STRINGIFY(eps)).c_str()); \
			TEST_VERIFY_THROW(result); \
		} \
	} \
	while (false)

namespace zf_test
{
	class equal_to {
	public:
		template <typename A, typename B>
		bool operator()(const A &a, const B &b) const
		{
			return a == b;
		}
	};

	template <typename A, typename B, typename F>
	void test_verify_relation(const A &a, const char *const as,
							  const B &b, const char *const bs,
							  const F &f, const char *const message,
							  const char *const fname, const unsigned fline)
	{
		if (!f(a, b))
		{
			zf_test::test_result result(message);
			result.add("left", strformat("%s (%s)", zf_test::to_string(a).c_str(), as).c_str());
			result.add("right", strformat("%s (%s)", zf_test::to_string(b).c_str(), bs).c_str());
			throw zf_test::test_verify_exception(fname, fline, result);
		}
	}
}

#define TEST_VERIFY_RELATION(a, b, relation, message) \
	do { \
		zf_test::test_verify_relation(a, STRINGIFY(a), b, STRINGIFY(b), zf_test::equal_to(), message, __FILE__, __LINE__); \
	} \
	while (false)

#define TEST_VERIFY_EQUAL(a, b) \
	TEST_VERIFY_RELATION(a, b, zf_test::equal_to, "not equal")
#define TEST_VERIFY_NOT_EQUAL(a, b) \
	TEST_VERIFY_RELATION(a, b, std::not_equal_to<void>(), "equal")
#define TEST_VERIFY_LESS_OR_EQUAL(a, b) \
	TEST_VERIFY_RELATION(a, b, std::less_equal<void>(), "not less or equal (<=)")
#define TEST_VERIFY_LESS(a, b) \
	TEST_VERIFY_RELATION(a, b, std::less<void>(), "not less (<)")
#define TEST_VERIFY_GREATER_OR_EQUAL(a, b) \
	TEST_VERIFY_RELATION(a, b, std::greater_equal<void>(), "not greater or equal (>=)")
#define TEST_VERIFY_GREATER(a, b) \
	TEST_VERIFY_RELATION(a, b, std::greater<void>(), "not greater (>)")

#define TEST_RUNNER_CREATE(argc, argv) \
	zf_test::test_runner test_runner_instance(argc, argv)

#define TEST_SUIT_ARGUMENTS \
	zf_test::test_runner &test_runner_instance

#define TEST_EXECUTE(f) \
	do { \
		const char *const prev_test_name = test_runner_instance.test_name; \
		test_runner_instance.test_name = STRINGIFY(f); \
		if (0 < test_runner_instance.verbosity) \
		{ \
			fprintf(stderr, "test: %s\n", test_runner_instance.test_name); \
		} \
		try \
		{ \
			f; \
		} \
		catch (const zf_test::test_verify_exception &e) \
		{ \
			++test_runner_instance.error_count; \
			zf_test::test_result result(e.result); \
			if (nullptr != test_runner_instance.suite_name) \
			{ \
				result.add("suite", test_runner_instance.suite_name); \
			} \
			result.add("test", test_runner_instance.test_name); \
			fprintf(stderr, "%s:%u: %s:\n", e.file.c_str(), e.line, result.message.c_str()); \
			result.fprint(stderr, "    "); \
		} \
		test_runner_instance.test_name = prev_test_name; \
	} \
	while (false)

#define TEST_EXECUTE_SUITE(s) \
	do { \
		const char *const prev_suite_name = test_runner_instance.suite_name; \
		test_runner_instance.suite_name = STRINGIFY(s); \
		if (0 < test_runner_instance.verbosity) { \
			fprintf(stderr, "suite: %s\n", test_runner_instance.suite_name); \
		} \
		s(test_runner_instance); \
		test_runner_instance.suite_name = prev_suite_name; \
	} \
	while (false)

#define TEST_RUNNER_EXIT_CODE() \
	(0 == test_runner_instance.error_count? 0: -1)
