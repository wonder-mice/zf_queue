#pragma once

#ifndef _ZF_QUEUE_H_
#define _ZF_QUEUE_H_

template <typename T>
struct zf_slist_entry
{
	T *next;
};

template <typename T, zf_slist_entry<T> T:: *entry>
struct zf_slist_head
{
	T *next;
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
	h->next = 0;
}

template <typename T, zf_slist_entry<T> T:: *entry>
bool zf_slist_empty(zf_slist_head<T, entry> *const h)
{
	return 0 == h->next;
}

template <typename T, zf_slist_entry<T> T:: *entry>
T *zf_slist_first(zf_slist_head<T, entry> *const h)
{
	return h->next;
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
	(e->*entry).next = h->next;
	h->next = e;
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
