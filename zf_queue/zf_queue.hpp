#pragma once

#ifndef _ZF_QUEUE_HPP_
#define _ZF_QUEUE_HPP_

#include "zf_queue.h"

template <typename Entry, typename Node>
Entry *zf_entry_(Node *const node, Node Entry::* field)
{
	return (Entry* )((char *)node - (size_t)&((Entry *)0->*field));
}

/*
 * Singly-linked list
 */
template <typename T>
struct zf_slist_node_: zf_slist_node
{
};

template <typename T, zf_slist_node_<T> T:: *node>
struct zf_slist_head_: zf_slist_head
{
};

template <typename T, zf_slist_node_<T> T:: *node>
T *zf_slist_first_(zf_slist_head_<T, node> *const h)
{
	return zf_entry_(zf_slist_first(&h), node);
}

template <typename T, zf_slist_node_<T> T:: *node>
T *zf_slist_next_(const zf_slist_head_<T, node> *const, T *const e)
{
	return zf_entry_(zf_slist_next(&(e->*node)), node);
}

/*
 * Tail queue
 */
template <typename T>
struct zf_tailq_node_: zf_tailq_node {};

template <typename T, zf_tailq_node T:: *node>
struct zf_tailq_head_: zf_tailq_head {};

template <typename T, zf_tailq_node T:: *node>
T *zf_tailq_entry_(zf_tailq_head_<T, node> *const, zf_tailq_node *const n)
{
	return zf_entry_(n, node);
}

template <typename T, zf_tailq_node T:: *node>
T *zf_tailq_first_(zf_tailq_head_<T, node> *const h)
{
	return zf_entry_(zf_tailq_first(h), node);
}

template <typename T, zf_tailq_node T:: *node>
T *zf_tailq_last_(zf_tailq_head_<T, node> *const h)
{
	return zf_entry_(zf_tailq_last(h), node);
}

template <typename T, zf_tailq_node T:: *node>
T *zf_tailq_end_(zf_tailq_head_<T, node> *const)
{
	return (T* )((char *)0 - (size_t)&((T *)0->*node));
}

template <typename T, zf_tailq_node T:: *node>
T *zf_tailq_next_(zf_tailq_head_<T, node> *const, T *const e)
{
	return zf_entry_(zf_tailq_next(&(e->*node)), node);
}

template <typename T, zf_tailq_node T:: *node>
T *zf_tailq_prev_(zf_tailq_head_<T, node> *const, T *const e)
{
	return zf_entry_(zf_tailq_prev(&(e->*node)), node);
}

template <typename T, zf_tailq_node T:: *node>
void zf_tailq_insert_head_(zf_tailq_head_<T, node> *const h, T *const e)
{
	zf_tailq_insert_head(h, &(e->*node));
}

template <typename T, zf_tailq_node T:: *node>
void zf_tailq_insert_tail_(zf_tailq_head_<T, node> *const h, T *const e)
{
	zf_tailq_insert_tail(h, &(e->*node));
}

template <typename T, zf_tailq_node T:: *node>
void zf_tailq_insert_before_(zf_tailq_head_<T, node> *const,
							 T *const a, T *const e)
{
	zf_tailq_insert_before(&(a->*node), &(e->*node));
}

template <typename T, zf_tailq_node T:: *node>
void zf_tailq_insert_after_(zf_tailq_head_<T, node> *const h,
							 T *const b, T *const e)
{
	zf_tailq_insert_after(h, &(b->*node), &(e->*node));
}

template <typename T, zf_tailq_node T:: *node>
void zf_tailq_remove_(zf_tailq_head_<T, node> *const h, T *const e)
{
	zf_tailq_remove(h, &(e->*node));
}

template <typename T, zf_tailq_node T:: *node, typename F>
void zf_tailq_foreach_(zf_tailq_head_<T, node> *const h, F f)
{
	zf_tailq_foreach(h, n)
	{
		f(zf_tailq_entry_(h, n));
	}
}

#endif
