#pragma once

#ifndef _ZF_QUEUE_H_
#define _ZF_QUEUE_H_

/* Define ZF_QUEUE_VERSION_REQUIRED to current value of ZF_QUEUE_VERSION before
 * including this file (or via compiler command line). In that case compilation
 * will break when non-compatible change is introduced.
 */
#define ZF_QUEUE_VERSION 1
#if defined(ZF_QUEUE_VERSION_REQUIRED)
	#if ZF_QUEUE_VERSION_REQUIRED != ZF_QUEUE_VERSION
		#error zf_queue version mismatch
	#endif
#endif

/* This file defines four types of data structures: singly-linked lists,
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
 * A list is headed by a single forward pointer (or an array of forward
 * pointers for a hash table header). The elements are doubly linked
 * so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before
 * or after an existing element or at the head of the list. A list
 * may be traversed in either direction.
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
 * A tail queue is headed by a pair of pointers, one to the head of the
 * list and the other to the tail of the list. The elements are doubly
 * linked so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before or
 * after an existing element, at the head of the list, or at the end of
 * the list. A tail queue may be traversed in either direction.
 *
 *                              SLIST   LIST    STAILQ  TAILQ
 * _node                        +       +       +       +
 * _head                        +       +       +       +
 * _INITIALIZER                 +       +       +       +
 * _init                        +       +       +       +
 * _empty                       +       +       +       +
 * _first                       +       +       +       +
 * _last                        -       -       +       +
 * _begin                       +       +       #       +
 * _end                         +       +       #       +
 * _rbegin                      -       -       -       #
 * _rend                        -       +       -       #
 * _next                        +       +       +       +
 * _prev                        -       +       -       +
 * _insert_head                 +       +       +       +
 * _insert_tail                 -       -       +       +
 * _insert_before               -       +       -       +
 * _insert_after                +       +       +       +
 * _remove                      -       +       -       +
 * _remove_head                 +       -       +       -
 * _remove_after                +       -       +       -
 * _concat                      -       #       #       #
 * _swap                        +       #       #       #
 * Experimental (no tests):
 * _foreach                     #       #       #       +
 * _foreach_from                #       #       #       +
 *
 * _FOREACH_FROM                #       #       #       #
 * _FOREACH_SAFE                #       #       #       #
 * _FOREACH_FROM_SAFE           #       #       #       #
 * _FOREACH_REVERSE             -       -       -       #
 * _FOREACH_REVERSE_FROM        -       -       -       #
 * _FOREACH_REVERSE_SAFE        -       -       -       #
 * _FOREACH_REVERSE_FROM_SAFE   -       -       -       #
 *
 * Where:
 *  "-" - operation is not supported by that data structure
 *  "+" - operation is supported and implemented
 *  "#" - operation is supported, but not implemented (yet)
 *
 * "Node" is a field inside "entry". "Node" allows "entry" to be a list item.
 * "Entry" has one or more "nodes" as fields and can be used as a list item.
 *   struct Entry
 *   {
 *       Node node;
 *   };
 *
 *   List EntryList;
 *
 * Functions zf_xxx_first() and zf_xxx_last() only work with non-empty lists.
 * Behaviour of those functions is undefined for empty lists.
 *
 * Functions zf_xxx_begin(), zf_xxx_end(), zf_xxx_rbegin() and zf_xxx_rend()
 * could be used with empty lists too.
 * For empty list h:
 *   zf_xxx_begin(h) == zf_xxx_end(h)
 *   zf_xxx_rbegin(h) == zf_xxx_rend(h)
 * For last node n of list h:
 *   zf_xxx_next(n) == zf_xxx_end(h)
 * For first node n of list h:
 *   zf_xxx_prev(n) == zf_xxx_rend(h)
 * The same is true for C++ extensions zf_xxx_yyy_().
 *
 * Parameter names:
 *   h - list Head
 *   n - some node
 *   e - some entry
 *   a - node or entry that goes after
 *   b - node or entry that goes before
 */

#include <stddef.h>
#include <stdbool.h>

#define _ZF_QUEUE_DECL static inline

#if defined(__cplusplus) && __cplusplus >= 201103L
	#define _ZF_QUEUE_CONSTEXPR constexpr
#else
	#define _ZF_QUEUE_CONSTEXPR
#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
	#define _ZF_QUEUE_NOEXCEPT noexcept
#elif defined(__cplusplus)
	#define _ZF_QUEUE_NOEXCEPT throw()
#else
	#define _ZF_QUEUE_NOEXCEPT
#endif

#define zf_entry(node, entry_type, entry_member) \
	((entry_type *)((char *)node - offsetof(entry_type, entry_member)))

/*
 * Singly-linked list
 */
typedef struct zf_slist_node
{
	struct zf_slist_node *next;
}
zf_slist_node;

typedef struct zf_slist_head
{
	struct zf_slist_node *first;
}
zf_slist_head;

#define ZF_SLIST_INITIALIZER() {0}

#ifdef __cplusplus
	_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
	zf_slist_head _zf_slist_initializer()
		_ZF_QUEUE_NOEXCEPT
	{
	#if __cplusplus >= 201103L
		return ZF_SLIST_INITIALIZER();
	#else
		const zf_slist_head init = ZF_SLIST_INITIALIZER();
		return init;
	#endif
	}
	#undef ZF_SLIST_INITIALIZER
	#define ZF_SLIST_INITIALIZER() _zf_slist_initializer()
#endif

_ZF_QUEUE_DECL
void zf_slist_init(struct zf_slist_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	h->first = 0;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
bool zf_slist_empty(struct zf_slist_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return 0 == h->first;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_slist_node *zf_slist_first(struct zf_slist_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->first;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_slist_node *zf_slist_begin(struct zf_slist_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->first;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_slist_node *zf_slist_end(struct zf_slist_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return (void)h, (zf_slist_node *)0;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_slist_node *zf_slist_next(struct zf_slist_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	return n->next;
}

_ZF_QUEUE_DECL
void zf_slist_insert_head(struct zf_slist_head *const h,
						  struct zf_slist_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	n->next = h->first;
	h->first = n;
}

/* insert a after b */
_ZF_QUEUE_DECL
void zf_slist_insert_after(struct zf_slist_node *const b,
						   struct zf_slist_node *const a)
	_ZF_QUEUE_NOEXCEPT
{
	a->next = b->next;
	b->next = a;
}

_ZF_QUEUE_DECL
void zf_slist_remove_head(struct zf_slist_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	h->first = h->first->next;
}

_ZF_QUEUE_DECL
void zf_slist_remove_after(struct zf_slist_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	n->next = n->next->next;
}

_ZF_QUEUE_DECL
void zf_slist_swap(struct zf_slist_head *const h1,
				   struct zf_slist_head *const h2)
	_ZF_QUEUE_NOEXCEPT
{
	struct zf_slist_node *const n = h1->first;
	h1->first = h2->first;
	h2->first = n;
}

/*
 * List
 */
typedef struct zf_list_node
{
	struct zf_list_node *next;
	struct zf_list_node **pprev;
}
zf_list_node;

typedef struct zf_list_head
{
	struct zf_list_node *first;
}
zf_list_head;

#define ZF_LIST_INITIALIZER() {0}

#ifdef __cplusplus
	_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
	zf_list_head _zf_list_initializer()
		_ZF_QUEUE_NOEXCEPT
	{
	#if __cplusplus >= 201103L
		return ZF_LIST_INITIALIZER();
	#else
		const zf_list_head init = ZF_LIST_INITIALIZER();
		return init;
	#endif
	}
	#undef ZF_LIST_INITIALIZER
	#define ZF_LIST_INITIALIZER() _zf_list_initializer()
#endif

_ZF_QUEUE_DECL
void zf_list_init(struct zf_list_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	h->first = 0;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
bool zf_list_empty(struct zf_list_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return 0 == h->first;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_list_node *zf_list_first(struct zf_list_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->first;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_list_node *zf_list_begin(struct zf_list_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->first;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_list_node *zf_list_end(struct zf_list_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return (void)h, (zf_list_node *)0;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_list_node *zf_list_rend(struct zf_list_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return (void)h, (zf_list_node *)0;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_list_node *zf_list_prev(struct zf_list_head *const h,
								  struct zf_list_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	return n->pprev == &h->first? 0: (zf_list_node *)
			((char *)n->pprev - offsetof(zf_list_node, next));
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_list_node *zf_list_next(struct zf_list_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	return n->next;
}

_ZF_QUEUE_DECL
void zf_list_insert_head(struct zf_list_head *const h,
						 struct zf_list_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 != (n->next = h->first))
	{
		h->first->pprev = &n->next;
	}
	h->first = n;
	n->pprev = &h->first;
}

/* insert b before a */
_ZF_QUEUE_DECL
void zf_list_insert_before(struct zf_list_node *const a,
						   struct zf_list_node *const b)
	_ZF_QUEUE_NOEXCEPT
{
	b->pprev = a->pprev;
	b->next = a;
	*a->pprev = b;
	a->pprev = &b->next;
}

/* insert a after b */
_ZF_QUEUE_DECL
void zf_list_insert_after(struct zf_list_node *const b,
						  struct zf_list_node *const a)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 != (a->next = b->next))
	{
		b->next->pprev = &a->next;
	}
	b->next = a;
	a->pprev = &b->next;
}

_ZF_QUEUE_DECL
void zf_list_remove(struct zf_list_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 != n->next)
	{
		n->next->pprev = n->pprev;
	}
	*n->pprev = n->next;
}

/*
 * Singly-linked tail queue
 */
typedef struct zf_stailq_node
{
	struct zf_stailq_node *next;
}
zf_stailq_node;

typedef struct zf_stailq_head
{
	struct zf_stailq_node first;
	struct zf_stailq_node *last;
}
zf_stailq_head;

#define ZF_STAILQ_INITIALIZER(h) {{0}, &(h)->first}

#ifdef __cplusplus
	_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
	zf_stailq_head _zf_stailq_initializer(zf_stailq_head *const h)
		_ZF_QUEUE_NOEXCEPT
	{
	#if __cplusplus >= 201103L
		return ZF_STAILQ_INITIALIZER(h);
	#else
		const zf_stailq_head init = ZF_STAILQ_INITIALIZER(h);
		return init;
	#endif
	}
	#undef ZF_STAILQ_INITIALIZER
	#define ZF_STAILQ_INITIALIZER(h) _zf_stailq_initializer(h)
#endif

_ZF_QUEUE_DECL
void zf_stailq_init(struct zf_stailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	h->first.next = 0;
	h->last = &h->first;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
bool zf_stailq_empty(struct zf_stailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return 0 == h->first.next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_stailq_node *zf_stailq_first(struct zf_stailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->first.next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_stailq_node *zf_stailq_last(struct zf_stailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return 0 == h->first.next? 0: h->last;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_stailq_node *zf_stailq_begin(struct zf_stailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->first.next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_stailq_node *zf_stailq_end(struct zf_stailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return (void)h, (zf_stailq_node *)0;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_stailq_node *zf_stailq_next(struct zf_stailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	return n->next;
}

_ZF_QUEUE_DECL
void zf_stailq_insert_head(struct zf_stailq_head *const h,
						   struct zf_stailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 == (n->next = h->first.next))
	{
		h->last = n;
	}
	h->first.next = n;
}

_ZF_QUEUE_DECL
void zf_stailq_insert_tail(struct zf_stailq_head *const h,
						   struct zf_stailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	n->next = 0;
	h->last->next = n;
	h->last = n;
}

_ZF_QUEUE_DECL
void zf_stailq_insert_after(struct zf_stailq_head *const h,
							struct zf_stailq_node *const p,
							struct zf_stailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 == (n->next = p->next))
	{
		h->last = n;
	}
	p->next = n;
}

_ZF_QUEUE_DECL
void zf_stailq_remove_head(struct zf_stailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 == (h->first.next = h->first.next->next))
	{
		h->last = &h->first;
	}
}

_ZF_QUEUE_DECL
void zf_stailq_remove_after(struct zf_stailq_head *const h,
							struct zf_stailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 == (n->next = n->next->next))
	{
		h->last = n;
	}
}

/*
 * Tail queue
 */
typedef struct zf_tailq_node
{
	struct zf_tailq_node *next;
	struct zf_tailq_node *prev;
}
zf_tailq_node;

typedef struct zf_tailq_head
{
	struct zf_tailq_node head;
}
zf_tailq_head;

#define ZF_TAILQ_INITIALIZER(h) {{0, &(h)->head}}

#ifdef __cplusplus
	_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
	zf_tailq_head _zf_tailq_initializer(zf_tailq_head *const h)
		_ZF_QUEUE_NOEXCEPT
	{
	#if __cplusplus >= 201103L
		return ZF_TAILQ_INITIALIZER(h);
	#else
		const zf_tailq_head init = ZF_TAILQ_INITIALIZER(h);
		return init;
	#endif
	}
	#undef ZF_TAILQ_INITIALIZER
	#define ZF_TAILQ_INITIALIZER(h) _zf_tailq_initializer((h))
#endif

_ZF_QUEUE_DECL
void zf_tailq_init(struct zf_tailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	h->head.next = 0;
	h->head.prev = &h->head;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
bool zf_tailq_empty(struct zf_tailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return 0 == h->head.next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_tailq_node *zf_tailq_first(struct zf_tailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->head.next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_tailq_node *zf_tailq_last(struct zf_tailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->head.prev->prev->next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_tailq_node *zf_tailq_begin(struct zf_tailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return h->head.next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_tailq_node *zf_tailq_end(struct zf_tailq_head *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return (void)h, (zf_tailq_node *)0;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_tailq_node *zf_tailq_next(struct zf_tailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	return n->next;
}

_ZF_QUEUE_DECL _ZF_QUEUE_CONSTEXPR
struct zf_tailq_node *zf_tailq_prev(struct zf_tailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	return n->prev->prev->next;
}

_ZF_QUEUE_DECL
void zf_tailq_insert_head(struct zf_tailq_head *const h,
						  struct zf_tailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 != (n->next = h->head.next))
	{
		h->head.next->prev = n;
	}
	else
	{
		h->head.prev = n;
	}
	h->head.next = n;
	n->prev = &(h->head);
}

_ZF_QUEUE_DECL
void zf_tailq_insert_tail(struct zf_tailq_head *const h,
						  struct zf_tailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	n->next = 0;
	n->prev = h->head.prev;
	h->head.prev->next = n;
	h->head.prev = n;
}

_ZF_QUEUE_DECL
void zf_tailq_insert_before(struct zf_tailq_node *const p,
							struct zf_tailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	n->next = p;
	n->prev = p->prev;
	p->prev->next = n;
	p->prev = n;
}

_ZF_QUEUE_DECL
void zf_tailq_insert_after(struct zf_tailq_head *const h,
						   struct zf_tailq_node *const p,
						   struct zf_tailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 != (n->next = p->next))
	{
		n->next->prev = n;
	}
	else
	{
		h->head.prev = n;
	}
	p->next = n;
	n->prev = p;
}

_ZF_QUEUE_DECL
void zf_tailq_remove(struct zf_tailq_head *const h,
					 struct zf_tailq_node *const n)
	_ZF_QUEUE_NOEXCEPT
{
	if (0 != n->next)
	{
		n->next->prev = n->prev;
	}
	else
	{
		h->head.prev = n->prev;
	}
	n->prev->next = n->next;
}

#define zf_tailq_foreach(h, n) \
	for (struct zf_tailq_node *n = (h)->head.next; 0 != n; n = n->next)

#define zf_tailq_foreach_from(f, n) \
	for (struct zf_tailq_node *n = (f); 0 != n; n = n->next)

/* C++ support */
#ifdef __cplusplus

template <typename Entry, typename Node>
_ZF_QUEUE_CONSTEXPR
Entry *zf_entry_(Node *const node, Node Entry::* field)
	_ZF_QUEUE_NOEXCEPT
{
	return (Entry* )((char *)node - (size_t)&((Entry *)0->*field));
}

/*
 * Singly-linked list C++ support
 */
template <typename T, zf_slist_node T:: *node>
struct zf_slist_head_: zf_slist_head
{
	zf_slist_head_() {}
	zf_slist_head_(const zf_slist_head &h) _ZF_QUEUE_NOEXCEPT: zf_slist_head(h) {}
};

template <typename T, zf_slist_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_slist_first_(zf_slist_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_slist_first(h), node);
}

template <typename T, zf_slist_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_slist_begin_(zf_slist_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_slist_begin(h), node);
}

template <typename T, zf_slist_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_slist_end_(zf_slist_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_slist_end(h), node);
}

template <typename T, zf_slist_node T:: *node>
T *zf_slist_next_(const zf_slist_head_<T, node> *const, T *const e)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_slist_next(&(e->*node)), node);
}

template <typename T, zf_slist_node T:: *node>
void zf_slist_insert_head_(zf_slist_head_<T, node> *const h, T *const e)
	_ZF_QUEUE_NOEXCEPT
{
	zf_slist_insert_head(h, &(e->*node));
}

/* insert a after b */
template <typename T, zf_slist_node T:: *node>
void zf_slist_insert_after_(zf_slist_head_<T, node> *const,
							T *const b, T *const a)
	_ZF_QUEUE_NOEXCEPT
{
	zf_slist_insert_after(&(b->*node), &(a->*node));
}

template <typename T, zf_slist_node T:: *node>
void zf_slist_remove_after_(zf_slist_head_<T, node> *const, T *const e)
	_ZF_QUEUE_NOEXCEPT
{
	zf_slist_remove_after(&(e->*node));
}

/*
 * List C++ support
 */
template <typename T, zf_list_node T:: *node>
struct zf_list_head_: zf_list_head
{
	zf_list_head_() {}
	zf_list_head_(const zf_list_head &h) _ZF_QUEUE_NOEXCEPT: zf_list_head(h) {}
};

template <typename T, zf_list_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_list_first_(zf_list_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_list_first(h), node);
}

template <typename T, zf_list_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_list_begin_(zf_list_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_list_begin(h), node);
}

template <typename T, zf_list_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_list_end_(zf_list_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_list_end(h), node);
}

template <typename T, zf_list_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_list_rend_(zf_list_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_list_rend(h), node);
}

template <typename T, zf_list_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_list_next_(const zf_list_head_<T, node> *const, T *const e)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_list_next(&(e->*node)), node);
}

template <typename T, zf_list_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_list_prev_(zf_list_head_<T, node> *const h, T *const e)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_list_prev(h, &(e->*node)), node);
}

template <typename T, zf_list_node T:: *node>
void zf_list_insert_head_(zf_list_head_<T, node> *const h, T *const e)
	_ZF_QUEUE_NOEXCEPT
{
	zf_list_insert_head(h,  &(e->*node));
}

/* insert b before a */
template <typename T, zf_list_node T:: *node>
void zf_list_insert_before_(const zf_list_head_<T, node> *const,
							T *const a, T *const b)
	_ZF_QUEUE_NOEXCEPT
{
	zf_list_insert_before(&(a->*node), &(b->*node));
}

/* insert a after b */
template <typename T, zf_list_node T:: *node>
void zf_list_insert_after_(const zf_list_head_<T, node> *const,
						   T *const b, T *const a)
	_ZF_QUEUE_NOEXCEPT
{
	zf_list_insert_after(&(b->*node), &(a->*node));
}

template <typename T, zf_list_node T:: *node>
void zf_list_remove_(const zf_list_head_<T, node> *const, T *const e)
	_ZF_QUEUE_NOEXCEPT
{
	zf_list_remove(&(e->*node));
}

/*
 * Singly-linked tail queue C++ support
 */
template <typename T, zf_stailq_node T:: *node>
struct zf_stailq_head_: zf_stailq_head {
	zf_stailq_head_() {}
	zf_stailq_head_(const zf_stailq_head &h) _ZF_QUEUE_NOEXCEPT: zf_stailq_head(h) {}
};

template <typename T, zf_stailq_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_stailq_begin_(zf_stailq_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_stailq_begin(h), node);
}

template <typename T, zf_stailq_node T:: *node>
_ZF_QUEUE_CONSTEXPR
T *zf_stailq_end_(zf_stailq_head_<T, node> *const h)
	_ZF_QUEUE_NOEXCEPT
{
	return zf_entry_(zf_stailq_end(h), node);
}

/*
 * Tail queue C++ support
 */
template <typename T, zf_tailq_node T:: *node>
struct zf_tailq_head_: zf_tailq_head {
	zf_tailq_head_() {}
	zf_tailq_head_(const zf_tailq_head &h) _ZF_QUEUE_NOEXCEPT: zf_tailq_head(h) {}
};

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
T *zf_tailq_begin_(zf_tailq_head_<T, node> *const h)
{
	return zf_entry_(zf_tailq_begin(h), node);
}

template <typename T, zf_tailq_node T:: *node>
T *zf_tailq_end_(zf_tailq_head_<T, node> *const h)
{
	return zf_entry_(zf_tailq_end(h), node);
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

#endif // __cplusplus

/* C/C++ type macros are convenient when code will be used from both C and C++.
 * Example:
 *   // file: foo.h
 *   struct foo_entry {
 *       zf_tailq_node node;
 *   };
 *   struct foo {
 *       zf_tailq_head_t(foo_entry, &foo_entry::node) head;
 *   };
 * That way foo.h can be included in both C and C++ source files.
 */
#ifdef __cplusplus
	#define zf_slist_head_t(T, node_field) zf_slist_head_<T, &T::node_field>
	#define zf_list_head_t(T, node_field) zf_list_head_<T, &T::node_field>
	#define zf_stailq_head_t(T, node_field) zf_stailq_head_<T, &T::node_field>
	#define zf_tailq_head_t(T, node_field) zf_tailq_head_<T, &T::node_field>
#else
	#define zf_slist_head_t(T, node_field) zf_slist_head
	#define zf_list_head_t(T, node_field) zf_list_head
	#define zf_stailq_head_t(T, node_field) zf_stailq_head
	#define zf_tailq_head_t(T, node_field) zf_tailq_head
#endif

#endif // _ZF_QUEUE_H_
