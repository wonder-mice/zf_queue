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
 *                              SLIST	STAILQ  LIST	TAILQ
 * _node                        +       +       +       +
 * _head                        +       +       +       +
 * _INITIALIZER                 +       +       +       +
 * _init                        +       +       +       +
 * _empty                       +       +       +       +
 * _first                       +       +       +       +
 * _last                        -       +       -       +
 * _next                        +       +       +       +
 * _prev                        -       -       +       +
 * _insert_head                 +       +       +       +
 * _insert_tail                 -       +       -       +
 * _insert_before               -       -       +       +
 * _insert_after                +       +       +       +
 * _remove                      -       -       +       +
 * _remove_head                 +       +       -       -
 * _remove_after                +       +       -       -
 * _concat                      -
 * _swap                        +
 *
 * _foreach                     -       -       -       +
 * _foreach_from                -       -       -       +
 *
 * _FOREACH_FROM		+	+	+	+
 * _FOREACH_SAFE		+	+	+	+
 * _FOREACH_FROM_SAFE		+	+	+	+
 * _FOREACH_REVERSE		-	-	-	+
 * _FOREACH_REVERSE_FROM	-	-	-	+
 * _FOREACH_REVERSE_SAFE	-	-	-	+
 * _FOREACH_REVERSE_FROM_SAFE	-	-	-	+
 */

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _ZF_QUEUE_DECL static inline

#define zf_entry(node, entry_type, entry_member) \
	((entry_type *)((char *)node - offsetof(entry_type, entry_member)))

/*
 * Singly-linked list
 */
struct zf_slist_node
{
	struct zf_slist_node *next;
};

struct zf_slist_head
{
	struct zf_slist_node *first;
};

#define ZF_SLIST_INITIALIZER {0}

_ZF_QUEUE_DECL
void zf_slist_init(struct zf_slist_head *const h)
{
	h->first = 0;
}

_ZF_QUEUE_DECL
bool zf_slist_empty(struct zf_slist_head *const h)
{
	return 0 == h->first;
}

_ZF_QUEUE_DECL
struct zf_slist_node *zf_slist_first(struct zf_slist_head *const h)
{
	return h->first;
}

_ZF_QUEUE_DECL
struct zf_slist_node *zf_slist_next(struct zf_slist_node *const n)
{
	return n->next;
}

_ZF_QUEUE_DECL
void zf_slist_insert_head(struct zf_slist_head *const h,
						  struct zf_slist_node *const n)
{
	n->next = h->first;
	h->first = n;
}

_ZF_QUEUE_DECL
void zf_slist_insert_after(struct zf_slist_node *const b,
						   struct zf_slist_node *const a)
{
	a->next = b->next;
	b->next = a;
}

_ZF_QUEUE_DECL
void zf_slist_remove_head(struct zf_slist_head *const h)
{
	h->first = h->first->next;
}

_ZF_QUEUE_DECL
void zf_slist_remove_after(struct zf_slist_node *const n)
{
	n->next = n->next->next;
}

_ZF_QUEUE_DECL
void zf_slist_swap(struct zf_slist_head *const h1,
				   struct zf_slist_head *const h2)
{
	struct zf_slist_node *const n = h1->first;
	h1->first = h2->first;
	h2->first = n;
}

/*
 * Singly-linked tail queue
 */
struct zf_stailq_node
{
	struct zf_stailq_node *next;
};

struct zf_stailq_head
{
	struct zf_stailq_node first;
	struct zf_stailq_node *last;
};

#define ZF_STAILQ_INITIALIZER(h) {{0}, &(h)->first}

_ZF_QUEUE_DECL
void zf_stailq_init(struct zf_stailq_head *const h)
{
	h->first.next = 0;
	h->last = &h->first;
}

_ZF_QUEUE_DECL
bool zf_stailq_empty(struct zf_stailq_head *const h)
{
	return 0 == h->first.next;
}

_ZF_QUEUE_DECL
struct zf_stailq_node *zf_stailq_first(struct zf_stailq_head *const h)
{
	return h->first.next;
}

_ZF_QUEUE_DECL
struct zf_stailq_node *zf_stailq_last(struct zf_stailq_head *const h)
{
	return 0 == h->first.next? 0: h->last;
}

_ZF_QUEUE_DECL
struct zf_stailq_node *zf_stailq_next(struct zf_stailq_node *const n)
{
	return n->next;
}

_ZF_QUEUE_DECL
void zf_stailq_insert_head(struct zf_stailq_head *const h,
						   struct zf_stailq_node *const n)
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
{
	n->next = 0;
	h->last->next = n;
	h->last = n;
}

_ZF_QUEUE_DECL
void zf_stailq_insert_after(struct zf_stailq_head *const h,
							struct zf_stailq_node *const p,
							struct zf_stailq_node *const n)
{
	if (0 == (n->next = p->next))
	{
		h->last = n;
	}
	p->next = n;
}

_ZF_QUEUE_DECL
void zf_stailq_remove_head(struct zf_stailq_head *const h)
{
	if (0 == (h->first.next = h->first.next->next))
	{
		h->last = &h->first;
	}
}

_ZF_QUEUE_DECL
void zf_stailq_remove_after(struct zf_stailq_head *const h,
							struct zf_stailq_node *const n)
{
	if (0 == (n->next = n->next->next))
	{
		h->last = n;
	}
}

/*
 * List
 */
struct zf_list_node
{
	struct zf_list_node *next;
	struct zf_list_node **pprev;
};

struct zf_list_head
{
	struct zf_list_node *first;
};

#define ZF_LIST_INITIALIZER {0}

_ZF_QUEUE_DECL
void zf_list_init(struct zf_list_head *const h)
{
	h->first = 0;
}

_ZF_QUEUE_DECL
bool zf_list_empty(struct zf_list_head *const h)
{
	return 0 == h->first;
}

_ZF_QUEUE_DECL
struct zf_list_node *zf_list_first(struct zf_list_head *const h)
{
	return h->first;
}

_ZF_QUEUE_DECL
struct zf_list_node *zf_list_prev(struct zf_list_head *const h,
								  struct zf_list_node *const n)
{
	return n->pprev == &h->first? 0: (struct zf_list_node *)
			((char *)n->pprev - offsetof(struct zf_list_node, next));
}

_ZF_QUEUE_DECL
struct zf_list_node *zf_list_next(struct zf_list_node *const n)
{
	return n->next;
}

_ZF_QUEUE_DECL
void zf_list_insert_head(struct zf_list_head *const h,
						 struct zf_list_node *const n)
{
	if (0 != (n->next = h->first))
	{
		h->first->pprev = &n->next;
	}
	h->first = n;
	n->pprev = &h->first;
}

_ZF_QUEUE_DECL
void zf_list_insert_before(struct zf_list_node *const p,
						   struct zf_list_node *const n)
{
	n->pprev = p->pprev;
	n->next = p;
	*p->pprev = n;
	p->pprev = &n->next;
}

_ZF_QUEUE_DECL
void zf_list_insert_after(struct zf_list_node *const p,
						  struct zf_list_node *const n)
{
	if (0 != (n->next = p->next))
	{
		p->next->pprev = &n->next;
	}
	p->next = n;
	n->pprev = &p->next;
}

_ZF_QUEUE_DECL
void zf_list_remove(struct zf_list_node *const n)
{
	if (0 != n->next)
	{
		n->next->pprev = n->pprev;
	}
	*n->pprev = n->next;
}

/*
 * Tail queue
 */
struct zf_tailq_node
{
	struct zf_tailq_node *next;
	struct zf_tailq_node *prev;
};

struct zf_tailq_head
{
	struct zf_tailq_node head;
};

#define ZF_TAILQ_INITIALIZER(h) {{0, &(h)->head}}

_ZF_QUEUE_DECL
void zf_tailq_init(struct zf_tailq_head *const h)
{
	h->head.next = 0;
	h->head.prev = &h->head;
}

_ZF_QUEUE_DECL
bool zf_tailq_empty(struct zf_tailq_head *const h)
{
	return 0 == h->head.next;
}

_ZF_QUEUE_DECL
struct zf_tailq_node *zf_tailq_first(struct zf_tailq_head *const h)
{
	return h->head.next;
}

_ZF_QUEUE_DECL
struct zf_tailq_node *zf_tailq_last(struct zf_tailq_head *const h)
{
	return h->head.prev->prev->next;
}

_ZF_QUEUE_DECL
struct zf_tailq_node *zf_tailq_next(struct zf_tailq_node *const n)
{
	return n->next;
}

_ZF_QUEUE_DECL
struct zf_tailq_node *zf_tailq_prev(struct zf_tailq_node *const n)
{
	return n->prev->prev->next;
}

_ZF_QUEUE_DECL
void zf_tailq_insert_head(struct zf_tailq_head *const h,
						  struct zf_tailq_node *const n)
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
{
	n->next = 0;
	n->prev = h->head.prev;
	h->head.prev->next = n;
	h->head.prev = n;
}

_ZF_QUEUE_DECL
void zf_tailq_insert_before(struct zf_tailq_node *const p,
							struct zf_tailq_node *const n)
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

#ifdef __cplusplus
}
#endif

#endif
