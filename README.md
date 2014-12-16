zf_queue
========

Modern implementation of classic BSD's sys/queue.h

Library consists of single stand alone header file: include/zf_queue.hpp

#include "zf_queue.hpp"

```c++
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
	Event event;
	zf_tailq_insert_tail(&loop, &event);
}
```
