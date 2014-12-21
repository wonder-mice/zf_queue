#include"zf_test.hpp"
#include "zf_queue.h"

/*
 * Singly-linked list
 */
static void test_zf_slist_initializer()
{
	zf_slist_head h = ZF_SLIST_INITIALIZER;
	TEST_VERIFY_TRUE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_first(&h));
}

static void test_zf_slist_init()
{
	zf_slist_head h;
	zf_slist_init(&h);
	TEST_VERIFY_TRUE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_first(&h));
}

static void test_zf_slist_insert_head()
{
	zf_slist_head h = ZF_SLIST_INITIALIZER;
	zf_slist_node n0;
	zf_slist_insert_head(&h, &n0);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0));
	zf_slist_node n1;
	zf_slist_insert_head(&h, &n1);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0));
	TEST_VERIFY_EQUAL(&n0, zf_slist_next(&n1));
}

static void test_zf_slist_insert_after()
{
	zf_slist_head h = ZF_SLIST_INITIALIZER;
	zf_slist_node n0;
	zf_slist_insert_head(&h, &n0);
	zf_slist_node n1;
	zf_slist_insert_after(&n0, &n1);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n1));
	zf_slist_node n2;
	zf_slist_insert_after(&n1, &n2);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n0));
	TEST_VERIFY_EQUAL(&n2, zf_slist_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n2));
	zf_slist_node n3;
	zf_slist_insert_after(&n0, &n3);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(&n3, zf_slist_next(&n0));
	TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n3));
	TEST_VERIFY_EQUAL(&n2, zf_slist_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n2));
}

static void test_zf_slist_remove_head()
{
	zf_slist_head h = ZF_SLIST_INITIALIZER;
	zf_slist_node n0;
	zf_slist_insert_head(&h, &n0);
	zf_slist_node n1;
	zf_slist_insert_head(&h, &n1);
	zf_slist_node n2;
	zf_slist_insert_head(&h, &n2);
	zf_slist_remove_head(&h);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_slist_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0));
	zf_slist_remove_head(&h);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0));
	zf_slist_remove_head(&h);
	TEST_VERIFY_TRUE(zf_slist_empty(&h));
}

static void test_zf_slist_remove_after()
{
	zf_slist_head h = ZF_SLIST_INITIALIZER;
	zf_slist_node n0;
	zf_slist_insert_head(&h, &n0);
	zf_slist_node n1;
	zf_slist_insert_head(&h, &n1);
	zf_slist_node n2;
	zf_slist_insert_head(&h, &n2);
	zf_slist_remove_after(&n2);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n2, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_slist_next(&n2));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0));
	zf_slist_remove_after(&n2);
	TEST_VERIFY_FALSE(zf_slist_empty(&h));
	TEST_VERIFY_EQUAL(&n2, zf_slist_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_slist_next(&n0));
}

static void test_zf_slist_swap()
{
	zf_slist_head ha = ZF_SLIST_INITIALIZER;
	zf_slist_node na0;
	zf_slist_insert_head(&ha, &na0);
	zf_slist_node na1;
	zf_slist_insert_head(&ha, &na1);
	zf_slist_head hb = ZF_SLIST_INITIALIZER;
	zf_slist_node nb0;
	zf_slist_insert_head(&hb, &nb0);
	zf_slist_node nb1;
	zf_slist_insert_head(&hb, &nb1);
	zf_slist_swap(&ha, &hb);
	TEST_VERIFY_FALSE(zf_slist_empty(&ha));
	TEST_VERIFY_EQUAL(&nb1, zf_slist_first(&ha));
	TEST_VERIFY_EQUAL(&nb0, zf_slist_next(&nb1));
	TEST_VERIFY_FALSE(zf_slist_empty(&hb));
	TEST_VERIFY_EQUAL(&na1, zf_slist_first(&hb));
	TEST_VERIFY_EQUAL(&na0, zf_slist_next(&na1));
}

struct slist_test_entry
{
	unsigned a[3];
	zf_slist_node node;
	unsigned b[5];
};

static void test_zf_slist_entry()
{
	slist_test_entry e0;
	zf_slist_node *const n0 = &e0.node;
	TEST_VERIFY_EQUAL(&e0, zf_entry(n0, slist_test_entry, node));
#ifdef __cplusplus
	TEST_VERIFY_EQUAL(&e0, zf_entry_(n0, &slist_test_entry::node));
#endif
}

static void test_zf_slist(TEST_SUIT_ARGUMENTS)
{
	TEST_EXECUTE(test_zf_slist_initializer());
	TEST_EXECUTE(test_zf_slist_init());
	TEST_EXECUTE(test_zf_slist_insert_head());
	TEST_EXECUTE(test_zf_slist_insert_after());
	TEST_EXECUTE(test_zf_slist_entry());
	TEST_EXECUTE(test_zf_slist_remove_head());
	TEST_EXECUTE(test_zf_slist_remove_after());
	TEST_EXECUTE(test_zf_slist_swap());
}

/*
 * Singly-linked tail queue
 */
static void test_zf_stailq_initializer()
{
	zf_stailq_head h = ZF_STAILQ_INITIALIZER;
	TEST_VERIFY_TRUE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_last(&h));
}

static void test_zf_stailq_init()
{
	zf_stailq_head h;
	zf_stailq_init(&h);
	TEST_VERIFY_TRUE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_last(&h));
}

static void test_zf_stailq_insert_head()
{
	zf_stailq_head h = ZF_STAILQ_INITIALIZER;
	zf_stailq_node n0;
	zf_stailq_insert_head(&h, &n0);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n0));
	zf_stailq_node n1;
	zf_stailq_insert_head(&h, &n1);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n0));
	zf_stailq_node n2;
	zf_stailq_insert_head(&h, &n2);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_next(&n2));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n0));
}

static void test_zf_stailq_insert_tail()
{
	zf_stailq_head h = ZF_STAILQ_INITIALIZER;
	zf_stailq_node n0;
	zf_stailq_insert_tail(&h, &n0);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n0));
	zf_stailq_node n1;
	zf_stailq_insert_tail(&h, &n1);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n1));
	zf_stailq_node n2;
	zf_stailq_insert_tail(&h, &n2);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_next(&n0));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n2));
}

static void test_zf_stailq_insert_after()
{
	zf_stailq_head h = ZF_STAILQ_INITIALIZER;
	zf_stailq_node n0;
	zf_stailq_insert_head(&h, &n0);
	zf_stailq_node n1;
	zf_stailq_insert_after(&h, &n0, &n1);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n1));
	zf_stailq_node n2;
	zf_stailq_insert_after(&h, &n0, &n2);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_next(&n0));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_next(&n2));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n1));
	zf_stailq_node n3;
	zf_stailq_insert_after(&h, &n1, &n3);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n3, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_next(&n0));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_next(&n2));
	TEST_VERIFY_EQUAL(&n3, zf_stailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n3));
}

static void test_zf_stailq_remove_head()
{
	zf_stailq_head h = ZF_STAILQ_INITIALIZER;
	zf_stailq_node n0;
	zf_stailq_insert_tail(&h, &n0);
	zf_stailq_node n1;
	zf_stailq_insert_tail(&h, &n1);
	zf_stailq_node n2;
	zf_stailq_insert_tail(&h, &n2);
	zf_stailq_remove_head(&h);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n2));
	zf_stailq_remove_head(&h);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n2));
	zf_stailq_remove_head(&h);
	TEST_VERIFY_TRUE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_last(&h));
}

static void test_zf_stailq_remove_after()
{
	zf_stailq_head h = ZF_STAILQ_INITIALIZER;
	zf_stailq_node n0;
	zf_stailq_insert_tail(&h, &n0);
	zf_stailq_node n1;
	zf_stailq_insert_tail(&h, &n1);
	zf_stailq_node n2;
	zf_stailq_insert_tail(&h, &n2);
	zf_stailq_node n3;
	zf_stailq_insert_tail(&h, &n3);
	zf_stailq_remove_after(&h, &n0);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n3, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_next(&n0));
	TEST_VERIFY_EQUAL(&n3, zf_stailq_next(&n2));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n3));
	zf_stailq_remove_after(&h, &n2);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(&n2, zf_stailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n2));
	zf_stailq_remove_after(&h, &n0);
	TEST_VERIFY_FALSE(zf_stailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_stailq_last(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_stailq_next(&n0));
}

static void test_zf_stailq(TEST_SUIT_ARGUMENTS)
{
	TEST_EXECUTE(test_zf_stailq_initializer());
	TEST_EXECUTE(test_zf_stailq_init());
	TEST_EXECUTE(test_zf_stailq_insert_head());
	TEST_EXECUTE(test_zf_stailq_insert_tail());
	TEST_EXECUTE(test_zf_stailq_insert_after());
	TEST_EXECUTE(test_zf_stailq_remove_head());
	TEST_EXECUTE(test_zf_stailq_remove_after());
}

int main(int argc, char *argv[])
{
	TEST_RUNNER_CREATE(argc, argv);

	TEST_EXECUTE_SUITE(test_zf_slist);
	TEST_EXECUTE_SUITE(test_zf_stailq);

	return TEST_RUNNER_EXIT_CODE();
}
