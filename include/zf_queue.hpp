#pragma once

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
zf_tailq_head<T, entry> zf_tailq_initializer(zf_tailq_head<T, entry> *const h)
{
    const zf_tailq_head<T, entry> head = {{0, &h->root}};
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
