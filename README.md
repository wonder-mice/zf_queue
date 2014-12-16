zf_queue
========

Modern implementation of classic BSD's sys/queue.h

Library consists of single standalone header file: include/zf_queue.hpp

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
	TAILQ_INSERT_TAIL(&loop, &event1, entry);
	Event event2;
	event2.what = 2;
	TAILQ_INSERT_TAIL(&loop, &event2, entry);
	printf("First: %i\n", TAILQ_FIRST(&loop)->what);
	printf("Last: %i\n", TAILQ_LAST(&loop, EventQueue)->what);
}
```
