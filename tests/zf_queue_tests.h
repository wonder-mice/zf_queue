#pragma once

#if defined(__cplusplus)
#include "zf_test.hpp"
#else
#include "zf_test.h"
#endif
#include "zf_queue.h"

#if !defined(__cplusplus)
#define nullptr NULL
#endif

/*
 * Singly-linked list
 */
typedef struct slist_test_entry
{
	unsigned a[3];
	zf_slist_node node;
	unsigned b[5];
}
slist_test_entry;
#ifdef __cplusplus
typedef zf_slist_head_t(slist_test_entry, node) slist_test_head_;
#endif

static void test_zf_slist_entry()
{
	slist_test_entry e0;
	zf_slist_node *const n0 = &e0.node;
	TEST_VERIFY_EQUAL(&e0, zf_entry(n0, slist_test_entry, node));
#ifdef __cplusplus
	TEST_VERIFY_EQUAL(&e0, zf_entry_(n0, &slist_test_entry::node));
#endif
}

static void test_zf_slist_initializer()
{
	{
		zf_slist_head h = ZF_SLIST_INITIALIZER();
		TEST_VERIFY_TRUE(zf_slist_empty(&h));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
	}
#ifdef __cplusplus
	{
		slist_test_head_ hpp = ZF_SLIST_INITIALIZER();
		TEST_VERIFY_TRUE(zf_slist_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end(&hpp), zf_slist_begin(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
	}
#endif
}

static void test_zf_slist_init()
{
	{
		zf_slist_head h;
		zf_slist_init(&h);
		TEST_VERIFY_TRUE(zf_slist_empty(&h));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
	}
#ifdef __cplusplus
	{
		slist_test_head_ hpp;
		zf_slist_init(&hpp);
		TEST_VERIFY_TRUE(zf_slist_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end(&hpp), zf_slist_begin(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
	}
#endif
}

static void test_zf_slist_insert_head()
{
	{
		zf_slist_head h = ZF_SLIST_INITIALIZER();
		zf_slist_node n0;
		zf_slist_insert_head(&h, &n0);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n0));
		zf_slist_node n1;
		zf_slist_insert_head(&h, &n1);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n0));
		TEST_VERIFY_EQUAL(&n0, zf_slist_next(&n1));
	}
#ifdef __cplusplus
	{
		slist_test_head_ hpp = ZF_SLIST_INITIALIZER();
		slist_test_entry e0;
		zf_slist_insert_head_(&hpp, &e0);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e0));
		slist_test_entry e1;
		zf_slist_insert_head_(&hpp, &e1);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e0, zf_slist_next_(&hpp, &e1));
	}
#endif
}

static void test_zf_slist_insert_after()
{
	{
		zf_slist_head h = ZF_SLIST_INITIALIZER();
		zf_slist_node n0;
		zf_slist_insert_head(&h, &n0);
		zf_slist_node n1;
		zf_slist_insert_after(&n0, &n1);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n0));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n1));
		zf_slist_node n2;
		zf_slist_insert_after(&n1, &n2);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n0));
		TEST_VERIFY_EQUAL(&n2, zf_slist_next(&n1));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n2));
		zf_slist_node n3;
		zf_slist_insert_after(&n0, &n3);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(&n3, zf_slist_next(&n0));
		TEST_VERIFY_EQUAL(&n1, zf_slist_next(&n3));
		TEST_VERIFY_EQUAL(&n2, zf_slist_next(&n1));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n2));
	}
#ifdef __cplusplus
	{
		slist_test_head_ hpp = ZF_SLIST_INITIALIZER();
		slist_test_entry e0;
		zf_slist_insert_head_(&hpp, &e0);
		slist_test_entry e1;
		zf_slist_insert_after_(&hpp, &e0, &e1);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_slist_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e1));
		slist_test_entry e2;
		zf_slist_insert_after_(&hpp, &e1, &e2);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_slist_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e2, zf_slist_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e2));
		slist_test_entry e3;
		zf_slist_insert_after_(&hpp, &e0, &e3);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(&e3, zf_slist_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e1, zf_slist_next_(&hpp, &e3));
		TEST_VERIFY_EQUAL(&e2, zf_slist_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e2));
	}
#endif
}

static void test_zf_slist_remove_head()
{
	{
		zf_slist_head h = ZF_SLIST_INITIALIZER();
		zf_slist_node n0;
		zf_slist_insert_head(&h, &n0);
		zf_slist_node n1;
		zf_slist_insert_head(&h, &n1);
		zf_slist_node n2;
		zf_slist_insert_head(&h, &n2);
		zf_slist_remove_head(&h);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(&n0, zf_slist_next(&n1));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n0));
		zf_slist_remove_head(&h);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n0));
		zf_slist_remove_head(&h);
		TEST_VERIFY_TRUE(zf_slist_empty(&h));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
	}
#ifdef __cplusplus
	{
		slist_test_head_ hpp = ZF_SLIST_INITIALIZER();
		slist_test_entry e0;
		zf_slist_insert_head_(&hpp, &e0);
		slist_test_entry e1;
		zf_slist_insert_head_(&hpp, &e1);
		slist_test_entry e2;
		zf_slist_insert_head_(&hpp, &e2);
		zf_slist_remove_head(&hpp);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_slist_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e0));
		zf_slist_remove_head(&hpp);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e0));
		zf_slist_remove_head(&hpp);
		TEST_VERIFY_TRUE(zf_slist_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
	}
#endif
}

static void test_zf_slist_remove_after()
{
	{
		zf_slist_head h = ZF_SLIST_INITIALIZER();
		zf_slist_node n0;
		zf_slist_insert_head(&h, &n0);
		zf_slist_node n1;
		zf_slist_insert_head(&h, &n1);
		zf_slist_node n2;
		zf_slist_insert_head(&h, &n2);
		zf_slist_remove_after(&n2);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n2, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(&n0, zf_slist_next(&n2));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n0));
		zf_slist_remove_after(&n2);
		TEST_VERIFY_FALSE(zf_slist_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end(&h), zf_slist_begin(&h));
		TEST_VERIFY_EQUAL(&n2, zf_slist_first(&h));
		TEST_VERIFY_EQUAL(zf_slist_end(&h), zf_slist_next(&n0));
	}
#ifdef __cplusplus
	{
		slist_test_head_ hpp = ZF_SLIST_INITIALIZER();
		slist_test_entry e0;
		zf_slist_insert_head_(&hpp, &e0);
		slist_test_entry e1;
		zf_slist_insert_head_(&hpp, &e1);
		slist_test_entry e2;
		zf_slist_insert_head_(&hpp, &e2);
		zf_slist_remove_after_(&hpp, &e2);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e2, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_slist_next_(&hpp, &e2));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e0));
		zf_slist_remove_after_(&hpp, &e2);
		TEST_VERIFY_FALSE(zf_slist_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_slist_end_(&hpp), zf_slist_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e2, zf_slist_first_(&hpp));
		TEST_VERIFY_EQUAL(zf_slist_end_(&hpp), zf_slist_next_(&hpp, &e0));
	}
#endif
}

static void test_zf_slist_swap()
{
	zf_slist_head ha = ZF_SLIST_INITIALIZER();
	zf_slist_node na0;
	zf_slist_insert_head(&ha, &na0);
	zf_slist_node na1;
	zf_slist_insert_head(&ha, &na1);
	zf_slist_head hb = ZF_SLIST_INITIALIZER();
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

static void test_zf_slist(TEST_SUIT_ARGUMENTS)
{
	TEST_EXECUTE(test_zf_slist_entry());
	TEST_EXECUTE(test_zf_slist_initializer());
	TEST_EXECUTE(test_zf_slist_init());
	TEST_EXECUTE(test_zf_slist_insert_head());
	TEST_EXECUTE(test_zf_slist_insert_after());
	TEST_EXECUTE(test_zf_slist_remove_head());
	TEST_EXECUTE(test_zf_slist_remove_after());
	TEST_EXECUTE(test_zf_slist_swap());
}

/*
 * List
 */
typedef struct list_test_entry
{
	unsigned a[3];
	zf_list_node node;
	unsigned b[5];
}
list_test_entry;
#ifdef __cplusplus
typedef zf_list_head_t(list_test_entry, node) list_test_head_;
#endif

static void test_zf_list_entry()
{
	list_test_entry e0;
	zf_list_node *const n0 = &e0.node;
	TEST_VERIFY_EQUAL(&e0, zf_entry(n0, list_test_entry, node));
#ifdef __cplusplus
	TEST_VERIFY_EQUAL(&e0, zf_entry_(n0, &list_test_entry::node));
#endif
}

static void test_zf_list_initializer()
{
	{
		zf_list_head h = ZF_LIST_INITIALIZER();
		TEST_VERIFY_TRUE(zf_list_empty(&h));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_begin(&h));
	}
#ifdef __cplusplus
	{
		list_test_head_ hpp = ZF_LIST_INITIALIZER();
		TEST_VERIFY_TRUE(zf_list_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_list_end(&hpp), zf_list_begin(&hpp));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
	}
#endif
}

static void test_zf_list_init()
{
	{
		zf_list_head h;
		zf_list_init(&h);
		TEST_VERIFY_TRUE(zf_list_empty(&h));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_begin(&h));
	}
#ifdef __cplusplus
	{
		list_test_head_ hpp;
		zf_list_init(&hpp);
		TEST_VERIFY_TRUE(zf_list_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_list_end(&hpp), zf_list_begin(&hpp));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
	}
#endif
}

static void test_zf_list_insert_head()
{
	{
		zf_list_head h = ZF_LIST_INITIALIZER();
		zf_list_node n0;
		zf_list_insert_head(&h, &n0);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_list_first(&h));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n0));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n0));
		zf_list_node n1;
		zf_list_insert_head(&h, &n1);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n0, zf_list_next(&n1));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n1));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n0));
		TEST_VERIFY_EQUAL(&n1, zf_list_prev(&h, &n0));
		zf_list_node n2;
		zf_list_insert_head(&h, &n2);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n2, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_next(&n2));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n2));
		TEST_VERIFY_EQUAL(&n0, zf_list_next(&n1));
		TEST_VERIFY_EQUAL(&n2, zf_list_prev(&h, &n1));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n0));
		TEST_VERIFY_EQUAL(&n1, zf_list_prev(&h, &n0));
	}
#ifdef __cplusplus
	{
		list_test_head_ hpp = ZF_LIST_INITIALIZER();
		list_test_entry e0;
		zf_list_insert_head_(&hpp, &e0);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e0));
		list_test_entry e1;
		zf_list_insert_head_(&hpp, &e1);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e1, zf_list_prev_(&hpp, &e0));
		list_test_entry e2;
		zf_list_insert_head_(&hpp, &e2);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e2, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_next_(&hpp, &e2));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e2));
		TEST_VERIFY_EQUAL(&e0, zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(&e2, zf_list_prev_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e1, zf_list_prev_(&hpp, &e0));
	}
#endif
}

static void test_zf_list_insert_before()
{
	{
		zf_list_head h = ZF_LIST_INITIALIZER();
		zf_list_node n0;
		zf_list_insert_head(&h, &n0);
		zf_list_node n1;
		zf_list_insert_before(&n0, &n1);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n0, zf_list_next(&n1));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n1));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n0));
		TEST_VERIFY_EQUAL(&n1, zf_list_prev(&h, &n0));
		zf_list_node n2;
		zf_list_insert_before(&n0, &n2);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n2, zf_list_next(&n1));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n1));
		TEST_VERIFY_EQUAL(&n0, zf_list_next(&n2));
		TEST_VERIFY_EQUAL(&n1, zf_list_prev(&h, &n2));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n0));
		TEST_VERIFY_EQUAL(&n2, zf_list_prev(&h, &n0));
	}
#ifdef __cplusplus
	{
		list_test_head_ hpp = ZF_LIST_INITIALIZER();
		list_test_entry e0;
		zf_list_insert_head_(&hpp, &e0);
		list_test_entry e1;
		zf_list_insert_before_(&hpp, &e0, &e1);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e1, zf_list_prev_(&hpp, &e0));
		list_test_entry e2;
		zf_list_insert_before_(&hpp, &e0, &e2);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e2, zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e1));
		TEST_VERIFY_EQUAL(&e0, zf_list_next_(&hpp, &e2));
		TEST_VERIFY_EQUAL(&e1, zf_list_prev_(&hpp, &e2));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e2, zf_list_prev_(&hpp, &e0));
	}
#endif
}

static void test_zf_list_insert_after()
{
	{
		zf_list_head h = ZF_LIST_INITIALIZER();
		zf_list_node n0;
		zf_list_insert_head(&h, &n0);
		zf_list_node n1;
		zf_list_insert_after(&n0, &n1);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_next(&n0));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n0));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n1));
		TEST_VERIFY_EQUAL(&n0, zf_list_prev(&h, &n1));
		zf_list_node n2;
		zf_list_insert_after(&n0, &n2);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n0, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n2, zf_list_next(&n0));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n0));
		TEST_VERIFY_EQUAL(&n1, zf_list_next(&n2));
		TEST_VERIFY_EQUAL(&n0, zf_list_prev(&h, &n2));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n1));
		TEST_VERIFY_EQUAL(&n2, zf_list_prev(&h, &n1));
	}
#ifdef __cplusplus
	{
		list_test_head_ hpp = ZF_LIST_INITIALIZER();
		list_test_entry e0;
		zf_list_insert_head_(&hpp, &e0);
		list_test_entry e1;
		zf_list_insert_after_(&hpp, &e0, &e1);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e0));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(&e0, zf_list_prev_(&hpp, &e1));
		list_test_entry e2;
		zf_list_insert_after_(&hpp, &e0, &e2);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e0, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e2, zf_list_next_(&hpp, &e0));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e0));
		TEST_VERIFY_EQUAL(&e1, zf_list_next_(&hpp, &e2));
		TEST_VERIFY_EQUAL(&e0, zf_list_prev_(&hpp, &e2));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(&e2, zf_list_prev_(&hpp, &e1));
	}
#endif
}

static void test_zf_list_remove()
{
	{
		zf_list_head h = ZF_LIST_INITIALIZER();
		zf_list_node n0;
		zf_list_insert_head(&h, &n0);
		zf_list_node n1;
		zf_list_insert_after(&n0, &n1);
		zf_list_node n2;
		zf_list_insert_after(&n1, &n2);
		zf_list_node n3;
		zf_list_insert_after(&n2, &n3);
		zf_list_remove(&n0);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n2, zf_list_next(&n1));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n1));
		TEST_VERIFY_EQUAL(&n3, zf_list_next(&n2));
		TEST_VERIFY_EQUAL(&n1, zf_list_prev(&h, &n2));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n3));
		TEST_VERIFY_EQUAL(&n2, zf_list_prev(&h, &n3));
		zf_list_remove(&n3);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_first(&h));
		TEST_VERIFY_EQUAL(&n2, zf_list_next(&n1));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n1));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n2));
		TEST_VERIFY_EQUAL(&n1, zf_list_prev(&h, &n2));
		zf_list_remove(&n2);
		TEST_VERIFY_FALSE(zf_list_empty(&h));
		TEST_VERIFY_NOT_EQUAL(zf_list_end(&h), zf_list_begin(&h));
		TEST_VERIFY_EQUAL(&n1, zf_list_first(&h));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_next(&n1));
		TEST_VERIFY_EQUAL(zf_list_rend(&h), zf_list_prev(&h, &n1));
		zf_list_remove(&n1);
		TEST_VERIFY_TRUE(zf_list_empty(&h));
		TEST_VERIFY_EQUAL(zf_list_end(&h), zf_list_begin(&h));
	}
#ifdef __cplusplus
	{
		list_test_head_ hpp = ZF_LIST_INITIALIZER();
		list_test_entry e0;
		zf_list_insert_head_(&hpp, &e0);
		list_test_entry e1;
		zf_list_insert_after_(&hpp, &e0, &e1);
		list_test_entry e2;
		zf_list_insert_after_(&hpp, &e1, &e2);
		list_test_entry e3;
		zf_list_insert_after_(&hpp, &e2, &e3);
		zf_list_remove_(&hpp, &e0);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e2, zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e1));
		TEST_VERIFY_EQUAL(&e3, zf_list_next_(&hpp, &e2));
		TEST_VERIFY_EQUAL(&e1, zf_list_prev_(&hpp, &e2));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e3));
		TEST_VERIFY_EQUAL(&e2, zf_list_prev_(&hpp, &e3));
		zf_list_remove_(&hpp, &e3);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(&e2, zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e2));
		TEST_VERIFY_EQUAL(&e1, zf_list_prev_(&hpp, &e2));
		zf_list_remove_(&hpp, &e2);
		TEST_VERIFY_FALSE(zf_list_empty(&hpp));
		TEST_VERIFY_NOT_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
		TEST_VERIFY_EQUAL(&e1, zf_list_first_(&hpp));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_next_(&hpp, &e1));
		TEST_VERIFY_EQUAL(zf_list_rend_(&hpp), zf_list_prev_(&hpp, &e1));
		zf_list_remove_(&hpp, &e1);
		TEST_VERIFY_TRUE(zf_list_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_list_end_(&hpp), zf_list_begin_(&hpp));
	}
#endif
}

static void test_zf_list(TEST_SUIT_ARGUMENTS)
{
	TEST_EXECUTE(test_zf_list_entry());
	TEST_EXECUTE(test_zf_list_initializer());
	TEST_EXECUTE(test_zf_list_init());
	TEST_EXECUTE(test_zf_list_insert_head());
	TEST_EXECUTE(test_zf_list_insert_before());
	TEST_EXECUTE(test_zf_list_insert_after());
	TEST_EXECUTE(test_zf_list_remove());
}

/*
 * Singly-linked tail queue
 */
typedef struct stailq_test_entry
{
	unsigned a[3];
	zf_stailq_node node;
	unsigned b[5];
}
stailq_test_entry;
#ifdef __cplusplus
typedef zf_stailq_head_t(stailq_test_entry, node) stailq_test_head_;
#endif

static void test_zf_stailq_entry()
{
	stailq_test_entry e0;
	zf_stailq_node *const n0 = &e0.node;
	TEST_VERIFY_EQUAL(&e0, zf_entry(n0, stailq_test_entry, node));
#ifdef __cplusplus
	TEST_VERIFY_EQUAL(&e0, zf_entry_(n0, &stailq_test_entry::node));
#endif
}

static void test_zf_stailq_initializer()
{
	{
		zf_stailq_head h = ZF_STAILQ_INITIALIZER(&h);
		TEST_VERIFY_TRUE(zf_stailq_empty(&h));
		TEST_VERIFY_EQUAL(zf_stailq_end(&h), zf_stailq_begin(&h));
	}
#ifdef __cplusplus
	{
		stailq_test_head_ hpp = ZF_STAILQ_INITIALIZER(&hpp);
		TEST_VERIFY_TRUE(zf_stailq_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_stailq_end(&hpp), zf_stailq_begin(&hpp));
		TEST_VERIFY_EQUAL(zf_stailq_end_(&hpp), zf_stailq_begin_(&hpp));
	}
#endif
}

static void test_zf_stailq_init()
{
	{
		zf_stailq_head h;
		zf_stailq_init(&h);
		TEST_VERIFY_TRUE(zf_stailq_empty(&h));
		TEST_VERIFY_EQUAL(zf_stailq_end(&h), zf_stailq_begin(&h));
	}
#ifdef __cplusplus
	{
		stailq_test_head_ hpp;
		zf_stailq_init(&hpp);
		TEST_VERIFY_TRUE(zf_stailq_empty(&hpp));
		TEST_VERIFY_EQUAL(zf_stailq_end(&hpp), zf_stailq_begin(&hpp));
		TEST_VERIFY_EQUAL(zf_stailq_end_(&hpp), zf_stailq_begin_(&hpp));
	}
#endif
}

static void test_zf_stailq_insert_head()
{
	zf_stailq_head h = ZF_STAILQ_INITIALIZER(&h);
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
	zf_stailq_head h = ZF_STAILQ_INITIALIZER(&h);
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
	zf_stailq_head h = ZF_STAILQ_INITIALIZER(&h);
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
	zf_stailq_head h = ZF_STAILQ_INITIALIZER(&h);
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
	zf_stailq_head h = ZF_STAILQ_INITIALIZER(&h);
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
	TEST_EXECUTE(test_zf_stailq_entry());
	TEST_EXECUTE(test_zf_stailq_initializer());
	TEST_EXECUTE(test_zf_stailq_init());
	TEST_EXECUTE(test_zf_stailq_insert_head());
	TEST_EXECUTE(test_zf_stailq_insert_tail());
	TEST_EXECUTE(test_zf_stailq_insert_after());
	TEST_EXECUTE(test_zf_stailq_remove_head());
	TEST_EXECUTE(test_zf_stailq_remove_after());
}

/*
 * Tail queue
 */
static void test_zf_tailq_initializer()
{
	zf_tailq_head h = ZF_TAILQ_INITIALIZER(&h);
	TEST_VERIFY_TRUE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(zf_tailq_begin(&h), zf_tailq_end(&h));
}

static void test_zf_tailq_init()
{
	zf_tailq_head h;
	zf_tailq_init(&h);
	TEST_VERIFY_TRUE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_last(&h));
}

static void test_zf_tailq_insert_head()
{
	zf_tailq_head h = ZF_TAILQ_INITIALIZER(&h);
	zf_tailq_node n0;
	zf_tailq_insert_head(&h, &n0);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n0));
	zf_tailq_node n1;
	zf_tailq_insert_head(&h, &n1);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n0));
}

static void test_zf_tailq_insert_tail()
{
	zf_tailq_head h = ZF_TAILQ_INITIALIZER(&h);
	zf_tailq_node n0;
	zf_tailq_insert_tail(&h, &n0);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n0));
	zf_tailq_node n1;
	zf_tailq_insert_tail(&h, &n1);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_prev(&n1));
}

static void test_zf_tailq_insert_before()
{
	zf_tailq_head h = ZF_TAILQ_INITIALIZER(&h);
	zf_tailq_node n0;
	zf_tailq_insert_head(&h, &n0);
	zf_tailq_node n1;
	zf_tailq_insert_before(&n0, &n1);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n0));
	zf_tailq_node n2;
	zf_tailq_insert_before(&n1, &n2);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&n2));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n2));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n0));
	zf_tailq_node n3;
	zf_tailq_insert_before(&n0, &n3);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&n2));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n2));
	TEST_VERIFY_EQUAL(&n3, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_next(&n3));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n3));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(&n3, zf_tailq_prev(&n0));
}

static void test_zf_tailq_insert_after()
{
	zf_tailq_head h = ZF_TAILQ_INITIALIZER(&h);
	zf_tailq_node n0;
	zf_tailq_insert_head(&h, &n0);
	zf_tailq_node n1;
	zf_tailq_insert_after(&h, &n0, &n1);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_prev(&n1));
	zf_tailq_node n2;
	zf_tailq_insert_after(&h, &n1, &n2);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n0));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n2));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n2));
	zf_tailq_node n3;
	zf_tailq_insert_after(&h, &n0, &n3);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n3, zf_tailq_next(&n0));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n0));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_next(&n3));
	TEST_VERIFY_EQUAL(&n0, zf_tailq_prev(&n3));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(&n3, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n2));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n2));
}

static void test_zf_tailq_remove()
{
	zf_tailq_head h = ZF_TAILQ_INITIALIZER(&h);
	zf_tailq_node n0;
	zf_tailq_insert_head(&h, &n0);
	zf_tailq_node n1;
	zf_tailq_insert_tail(&h, &n1);
	zf_tailq_node n2;
	zf_tailq_insert_tail(&h, &n2);
	zf_tailq_node n3;
	zf_tailq_insert_tail(&h, &n3);
	zf_tailq_remove(&h, &n0);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n3, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(&n3, zf_tailq_next(&n2));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n2));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n3));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_prev(&n3));
	zf_tailq_remove(&h, &n3);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(&n2, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n2));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_prev(&n2));
	zf_tailq_remove(&h, &n2);
	TEST_VERIFY_FALSE(zf_tailq_empty(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_first(&h));
	TEST_VERIFY_EQUAL(&n1, zf_tailq_last(&h));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_next(&n1));
	TEST_VERIFY_EQUAL(nullptr, zf_tailq_prev(&n1));
	zf_tailq_remove(&h, &n1);
	TEST_VERIFY_TRUE(zf_tailq_empty(&h));
}

static void test_zf_tailq(TEST_SUIT_ARGUMENTS)
{
	TEST_EXECUTE(test_zf_tailq_initializer());
	TEST_EXECUTE(test_zf_tailq_init());
	TEST_EXECUTE(test_zf_tailq_insert_head());
	TEST_EXECUTE(test_zf_tailq_insert_tail());
	TEST_EXECUTE(test_zf_tailq_insert_before());
	TEST_EXECUTE(test_zf_tailq_insert_after());
	TEST_EXECUTE(test_zf_tailq_remove());
}

static void test_zf_queue_h(TEST_SUIT_ARGUMENTS)
{
	TEST_EXECUTE_SUITE(test_zf_slist);
	TEST_EXECUTE_SUITE(test_zf_list);
	TEST_EXECUTE_SUITE(test_zf_stailq);
	TEST_EXECUTE_SUITE(test_zf_tailq);
}
