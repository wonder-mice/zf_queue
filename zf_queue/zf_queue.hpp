#pragma once

#ifndef _ZF_QUEUE_HPP_
#define _ZF_QUEUE_HPP_

#include "zf_queue.h"

/*
 * Singly-linked list
 */
template <typename T>
struct zf_slist_node_: zf_slist_node
{
};

template <typename T, zf_slist_node_<T> T:: *entry>
struct zf_slist_head_: zf_slist_head
{
};

template <typename T, zf_slist_node_<T> T:: *entry>
T *zf_slist_first_(zf_slist_head_<T, entry> *const h)
{
	return zf_entry_(zf_slist_first(&h), entry);
}

template <typename T, zf_slist_node_<T> T:: *entry>
T *zf_slist_next_(const zf_slist_head_<T, entry> *const, T *const e)
{
	return zf_entry_(zf_slist_next(&(e->*entry)), entry);
}



#endif
