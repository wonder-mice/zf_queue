#include "zf_test.hpp"
#include "zf_queue.hpp"

namespace
{
	enum param_style
	{
		dummy_head,
		explicit_entry
	};

	struct slist_node
	{
		unsigned a[6];
		zf_slist_entry<slist_node> entry;
		unsigned b[7];
	};

	typedef zf_slist_head<slist_node, &slist_node::entry> slist_nodes;

	void test_slist_initializer()
	{
		slist_nodes ns = zf_slist_initializer(&ns);
		TEST_VERIFY_TRUE(zf_slist_empty(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_first(&ns));
	}

	void test_slist_initialize()
	{
		slist_nodes ns;
		zf_slist_init(&ns);
		TEST_VERIFY_TRUE(zf_slist_empty(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_first(&ns));
	}

	void test_slist_insert_head()
	{
		slist_nodes ns = zf_slist_initializer(&ns);
		slist_node n0;
		zf_slist_insert_head(&ns, &n0);
		TEST_VERIFY_FALSE(zf_slist_empty(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&ns, &n0));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0, &slist_node::entry));
		slist_node n1;
		zf_slist_insert_head(&ns, &n1);
		TEST_VERIFY_FALSE(zf_slist_empty(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_slist_first(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&ns, &n0));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0, &slist_node::entry));
		TEST_VERIFY_EQUAL(&n0, zf_slist_next(&ns, &n1));
		TEST_VERIFY_EQUAL(&n0, zf_slist_next(&n1, &slist_node::entry));
	}

	void test_slist_insert_after(const param_style style)
	{
		slist_nodes ns = zf_slist_initializer(&ns);
		slist_node n0;
		zf_slist_insert_head(&ns, &n0);
		slist_node n1;
		if (dummy_head == style)
			zf_slist_insert_after(&ns, &n0, &n1);
		else if (explicit_entry == style)
			zf_slist_insert_after(&n0, &n1, &slist_node::entry);
		TEST_VERIFY_FALSE(zf_slist_empty(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_slist_next(&ns, &n0));
		TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n0, &slist_node::entry));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&ns, &n1));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n1, &slist_node::entry));
		slist_node n2;
		if (dummy_head == style)
			zf_slist_insert_after(&ns, &n1, &n2);
		else if (explicit_entry == style)
			zf_slist_insert_after(&n1, &n2, &slist_node::entry);
		TEST_VERIFY_FALSE(zf_slist_empty(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_slist_next(&ns, &n0));
		TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n0, &slist_node::entry));
		TEST_VERIFY_EQUAL(&n2, zf_slist_next(&ns, &n1));
		TEST_VERIFY_EQUAL(&n2, zf_slist_next(&n1, &slist_node::entry));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&ns, &n2));
		TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n2, &slist_node::entry));
	}

	struct tailq_node
	{
		unsigned a[6];
		zf_tailq_entry<tailq_node> entry;
		unsigned b[7];
	};

	typedef zf_tailq_head<tailq_node, &tailq_node::entry> tailq_nodes;

	void test_tailq_initializer()
	{
		tailq_nodes ns = zf_tailq_initializer(&ns);
		TEST_VERIFY_TRUE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_last(&ns));
	}

	void test_tailq_initialize()
	{
		tailq_nodes ns;
		zf_tailq_init(&ns);
		TEST_VERIFY_TRUE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_last(&ns));
	}

	void test_tailq_insert_head()
	{
		tailq_nodes ns = zf_tailq_initializer(&ns);
		tailq_node n0;
		zf_tailq_insert_head(&ns, &n0);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n0));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n0));
		tailq_node n1;
		zf_tailq_insert_head(&ns, &n1);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n0));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&ns, &n0));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_next(&ns, &n1));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n1));
		tailq_node n2;
		zf_tailq_insert_head(&ns, &n2);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n0));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&ns, &n0));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_next(&ns, &n1));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_prev(&ns, &n1));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&ns, &n2));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n2));
	}

	void test_tailq_insert_tail()
	{
		tailq_nodes ns = zf_tailq_initializer(&ns);
		tailq_node n0;
		zf_tailq_insert_tail(&ns, &n0);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n0));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n0));
		tailq_node n1;
		zf_tailq_insert_tail(&ns, &n1);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&ns, &n0));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n0));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n1));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_prev(&ns, &n1));
		tailq_node n2;
		zf_tailq_insert_tail(&ns, &n2);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&ns, &n0));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n0));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_next(&ns, &n1));
		TEST_VERIFY_EQUAL(&n0, zf_tailq_prev(&ns, &n1));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n2));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&ns, &n2));
	}

	void test_tailq_remove()
	{
		tailq_nodes ns = zf_tailq_initializer(&ns);
		tailq_node n0;
		zf_tailq_insert_tail(&ns, &n0);
		tailq_node n1;
		zf_tailq_insert_tail(&ns, &n1);
		tailq_node n2;
		zf_tailq_insert_tail(&ns, &n2);
		tailq_node n3;
		zf_tailq_insert_tail(&ns, &n3);

		zf_tailq_remove(&ns, &n0);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n3, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_next(&ns, &n1));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n1));
		TEST_VERIFY_EQUAL(&n3, zf_tailq_next(&ns, &n2));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&ns, &n2));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n3));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_prev(&ns, &n3));
		zf_tailq_remove(&ns, &n3);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_next(&ns, &n1));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n1));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n2));
		TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&ns, &n2));
		zf_tailq_remove(&ns, &n1);
		TEST_VERIFY_FALSE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(&n2, zf_tailq_last(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&ns, &n2));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&ns, &n2));
		zf_tailq_remove(&ns, &n2);
		TEST_VERIFY_TRUE(zf_tailq_empty(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_first(&ns));
		TEST_VERIFY_EQUAL(nullptr, zf_tailq_last(&ns));
	}
}

int main(int argc, char *argv[])
{
	TEST_RUNNER_CREATE(argc, argv);

	TEST_EXECUTE(test_slist_initializer());
	TEST_EXECUTE(test_slist_initialize());
	TEST_EXECUTE(test_slist_insert_head());
	TEST_EXECUTE(test_slist_insert_after(dummy_head));
	TEST_EXECUTE(test_slist_insert_after(explicit_entry));

	TEST_EXECUTE(test_tailq_initializer());
	TEST_EXECUTE(test_tailq_initialize());
	TEST_EXECUTE(test_tailq_insert_head());
	TEST_EXECUTE(test_tailq_insert_tail());
	TEST_EXECUTE(test_tailq_remove());

	return TEST_RUNNER_EXIT_CODE();
}
