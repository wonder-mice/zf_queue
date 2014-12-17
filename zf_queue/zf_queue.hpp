#pragma once

#ifndef _ZF_QUEUE_H_
#define _ZF_QUEUE_H_

/*
 * This file defines four types of data structures: singly-linked lists,
 * singly-linked tail queues, lists and tail queues.
 *
 * A singly-linked list is headed by a single forward pointer. The elements
 * are singly linked for minimum space and pointer manipulation overhead at
 * the expense of O(n) removal for arbitrary elements. New elements can be
 * added to the list after an existing element or at the head of the list.
 * Elements being removed from the head of the list should use the explicit
 * macro for this purpose for optimum efficiency. A singly-linked list may
 * only be traversed in the forward direction.  Singly-linked lists are ideal
 * for applications with large datasets and few or no removals or for
 * implementing a LIFO queue.
 *
 * A singly-linked tail queue is headed by a pair of pointers, one to the
 * head of the list and the other to the tail of the list. The elements are
 * singly linked for minimum space and pointer manipulation overhead at the
 * expense of O(n) removal for arbitrary elements. New elements can be added
 * to the list after an existing element, at the head of the list, or at the
 * end of the list. Elements being removed from the head of the tail queue
 * should use the explicit macro for this purpose for optimum efficiency.
 * A singly-linked tail queue may only be traversed in the forward direction.
 * Singly-linked tail queues are ideal for applications with large datasets
 * and few or no removals or for implementing a FIFO queue.
 *
 * A list is headed by a single forward pointer (or an array of forward
 * pointers for a hash table header). The elements are doubly linked
 * so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before
 * or after an existing element or at the head of the list. A list
 * may be traversed in either direction.
 *
 * A tail queue is headed by a pair of pointers, one to the head of the
 * list and the other to the tail of the list. The elements are doubly
 * linked so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before or
 * after an existing element, at the head of the list, or at the end of
 * the list. A tail queue may be traversed in either direction.
 *
 *                              SLIST	LIST	STAILQ	TAILQ
 * _entry                       +       +       +       +
 * _head                        +       +       +       +
 * _initializer                 +       -       -       +
 * _init                        +       -       -       +
 * _empty                       +       -       -       +
 * _FIRST                       +       -       -       +
 * _NEXT                        +       -       -       +
 * _PREV			-	+	-	+
 * _LAST			-	-	+	+
 * _FOREACH			+	+	+	+
 * _FOREACH_FROM		+	+	+	+
 * _FOREACH_SAFE		+	+	+	+
 * _FOREACH_FROM_SAFE		+	+	+	+
 * _FOREACH_REVERSE		-	-	-	+
 * _FOREACH_REVERSE_FROM	-	-	-	+
 * _FOREACH_REVERSE_SAFE	-	-	-	+
 * _FOREACH_REVERSE_FROM_SAFE	-	-	-	+
 * _INSERT_HEAD			+	+	+	+
 * _INSERT_BEFORE		-	+	-	+
 * _INSERT_AFTER		+	+	+	+
 * _INSERT_TAIL			-	-	+	+
 * _CONCAT			-	-	+	+
 * _REMOVE_AFTER		+	-	+	-
 * _REMOVE_HEAD			+	-	+	-
 * _REMOVE			+	+	+	+
 * _SWAP			+	+	+	+
 */

/*
 * Singly-linked list
 */
template <typename T>
struct zf_slist_entry
{
	T *next;
};

template <typename T, zf_slist_entry<T> T:: *entry>
struct zf_slist_head
{
	T *first;
};

template <typename T, zf_slist_entry<T> T:: *entry>
zf_slist_head<T, entry> zf_slist_initializer(const zf_slist_head<T, entry> *const)
{
	const zf_slist_head<T, entry> head = {0};
	return head;
}

template <typename T, zf_slist_entry<T> T:: *entry>
void zf_slist_init(zf_slist_head<T, entry> *const h)
{
	h->first = 0;
}

template <typename T, zf_slist_entry<T> T:: *entry>
bool zf_slist_empty(zf_slist_head<T, entry> *const h)
{
	return 0 == h->first;
}

template <typename T, zf_slist_entry<T> T:: *entry>
T *zf_slist_first(zf_slist_head<T, entry> *const h)
{
	return h->first;
}


template <typename T>
T *zf_slist_next(const T *const e, zf_slist_entry<T> T:: *entry)
{
	return (e->*entry).next;
}

template <typename T, zf_slist_entry<T> T:: *entry>
T *zf_slist_next(zf_slist_head<T, entry> *const, const T *const e)
{
	return zf_slist_next(e, entry);
}

template <typename T, zf_slist_entry<T> T:: *entry>
void zf_slist_insert_head(zf_slist_head<T, entry> *const h, T *const e)
{
	(e->*entry).next = h->first;
	h->first = e;
}

template <typename T>
void zf_slist_insert_after(T *const b, T *const e, zf_slist_entry<T> T:: *entry)
{
	(e->*entry).next = (b->*entry).next;
	(b->*entry).next = e;
}

template <typename T, zf_slist_entry<T> T:: *entry>
void zf_slist_insert_after(zf_slist_head<T, entry> *const, T *const b, T *const e)
{
	zf_slist_insert_after(b, e, entry);
}

/*
 * List
 */
template <typename T>
struct zf_list_entry
{
	T *next;
	zf_list_entry<T> *prev;
};

template <typename T, zf_list_entry<T> T:: *entry>
struct zf_list_head
{
	T *first;
};

/*
 * Singly-linked tail queue
 */
template <typename T>
struct zf_stailq_entry
{
	T *next;
};

template <typename T, zf_list_entry<T> T:: *entry>
struct zf_stailq_head
{
	T *first;
	zf_stailq_entry<T> *last;
};

/*
 * Tail queue
 */
template <typename T>
struct zf_tailq_entry
{
	T *next;
	zf_tailq_entry<T> *prev;
};

template <typename T, zf_tailq_entry<T> T:: *entry>
struct zf_tailq_head
{
	zf_tailq_entry<T> root;
};

template <typename T, zf_tailq_entry<T> T:: *entry>
zf_tailq_head<T, entry> zf_tailq_initializer(const zf_tailq_head<T, entry> *const h)
{
	const zf_tailq_head<T, entry> head =
			{{0, const_cast<zf_tailq_entry<T> *>(&h->root)}};
	return head;
}

template <typename T, zf_tailq_entry<T> T:: *entry>
void zf_tailq_init(zf_tailq_head<T, entry> *const h)
{
	h->root.next = 0;
	h->root.prev = &h->root;
}

template <typename T, zf_tailq_entry<T> T:: *entry>
zf_tailq_entry<T> *zf_tailq_entry_ptr(const zf_tailq_head<T, entry> *const, T *const e)
{
	return &(e->*entry);
}

template <typename T, zf_tailq_entry<T> T:: *entry>
bool zf_tailq_empty(const zf_tailq_head<T, entry> *const h)
{
	return 0 == h->root.next;
}

template <typename T, zf_tailq_entry<T> T:: *entry>
T *zf_tailq_first(const zf_tailq_head<T, entry> *const h)
{
	return h->root.next;
}

template <typename T, zf_tailq_entry<T> T:: *entry>
T *zf_tailq_last(const zf_tailq_head<T, entry> *const h)
{
	return h->root.prev->prev->next;
}

template <typename T, zf_tailq_entry<T> T:: *entry>
T *zf_tailq_next(const zf_tailq_head<T, entry> *const, const T *const e)
{
	return (e->*entry).next;
}

template <typename T, zf_tailq_entry<T> T:: *entry>
T *zf_tailq_prev(const zf_tailq_head<T, entry> *const, const T *const e)
{
	return (e->*entry).prev->prev->next;
}

template <typename T, zf_tailq_entry<T> T:: *entry>
void zf_tailq_insert_head(zf_tailq_head<T, entry> *const h, T *const e)
{
	if (0 != ((e->*entry).next = h->root.next))
	{
		(h->root.next->*entry).prev = &(e->*entry);
	}
	else
	{
		h->root.prev = &(e->*entry);
	}
	h->root.next = e;
	(e->*entry).prev = &(h->root);
}

template <typename T, zf_tailq_entry<T> T:: *entry>
void zf_tailq_insert_tail(zf_tailq_head<T, entry> *const h, T *const e)
{
	(e->*entry).next = 0;
	(e->*entry).prev = h->root.prev;
	h->root.prev->next = e;
	h->root.prev = &(e->*entry);
}

template <typename T, zf_tailq_entry<T> T:: *entry>
void zf_tailq_remove(zf_tailq_head<T, entry> *const h, const T *const e)
{
	if (0 != (e->*entry).next)
	{
		((e->*entry).next->*entry).prev = (e->*entry).prev;
	}
	else
	{
		h->root.prev = (e->*entry).prev;
	}
	(e->*entry).prev->next = (e->*entry).next;
}

#endif /* !_ZF_QUEUE_H_ */
