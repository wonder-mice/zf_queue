zf_queue
========

About
--------
This is a blend of classic BSD's [sys/queue.h] design with [linux/list.h] implementation. 
As a bonus, library provides binary compatible C++ interface.

[sys/queue.h]: https://svnweb.freebsd.org/base/head/sys/sys/queue.h
[linux/list.h]: https://github.com/torvalds/linux/blob/master/include/linux/list.h

Library consists of single standalone header file:
[zf_queue/zf_queue.h](../blob/master/zf_queue/zf_queue.h)

Following example uses zf_queue.hpp:
```c++
#include "zf_queue.hpp"

struct Event
{
	int what;
	zf_tailq_entry<Event> entry;
};

struct Loop
{
	zf_tailq_head<Event, &Event::entry> events;
};

int main()
{
	Loop loop;
	Event event1;
	event1.what = 1;
	zf_tailq_insert_tail(&loop, &event1);
	Event event2;
	event2.what = 2;
	zf_tailq_insert_tail(&loop, &event2);
	printf("First: %i\n", zf_tailq_first(&loop)->what);
	printf("Last: %i\n", zf_tailq_last(&loop)->what);
}
```
This example uses classic queue.h. Notice that name of entry field must be specified explicitly for TAILQ_INSERT_TAIL and TAILQ_LAST requires the name of the structure that holds list head:
```c
#include "queue.h"

struct Event
{
	int what;
	TAILQ_ENTRY(Event) entry;
};

TAILQ_HEAD(EventQueue, Event);

struct Loop
{
	EventQueue events;
};

int main()
{
	Loop loop;
	Event event1;
	event1.what = 1;
	// Need to specify entry field name
	TAILQ_INSERT_TAIL(&loop, &event1, entry);
	Event event2;
	event2.what = 2;
	// Need to specify entry field name
	TAILQ_INSERT_TAIL(&loop, &event2, entry);
	printf("First: %i\n", TAILQ_FIRST(&loop)->what);
	// Need to specify head type name (EventQueue)
	printf("Last: %i\n", TAILQ_LAST(&loop, EventQueue)->what);
}
```
