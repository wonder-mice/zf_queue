#include "zf_test.hpp"
#include "zf_queue.hpp"

namespace
{
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
	TEST_EXECUTE(test_tailq_initializer());
	TEST_EXECUTE(test_tailq_initialize());
	TEST_EXECUTE(test_tailq_insert_head());
	TEST_EXECUTE(test_tailq_insert_tail());
	TEST_EXECUTE(test_tailq_remove());

	return TEST_RUNNER_EXIT_CODE();
}
