zf_queue
========

This is a blend of classic BSD [sys/queue.h] design with Linux [linux/list.h] implementation.
BSD implementation has a nice variaty of primitives (list, slist, tailq, stailq), but it uses
macros. Linux implementation less reach and has GPL license, but uses functions (more type
safety, better error messages) and has interesting design. This library tries to take the
best from both and mix it under BSD-style license.
It addition to C implementation, it also provides binary compatible C++ interface.

[sys/queue.h]: https://svnweb.freebsd.org/base/head/sys/sys/queue.h
[linux/list.h]: https://github.com/torvalds/linux/blob/master/include/linux/list.h

Usage
--------

This header-only library has two headers:
* [zf_queue.h](../blob/master/zf_queue/zf_queue.h) - C implementation
* [zf_queue.hpp](../blob/master/zf_queue/zf_queue.hpp) C++ interface

For C only the first one is necessary. For C++ you need both.

### Embedding

Put [zf_queue.h](../blob/master/zf_queue/zf_queue.h) into your source tree.
For C++ also add [zf_queue.hpp](../blob/master/zf_queue/zf_queue.hpp). Include as usual:
```c
#include "zf_queue.h"
```

### Embeding with CMake

Put [zf_queue](../blob/master/zf_queue) directory into your CMake project.
Add the following to CMakeLists.txt in parent directory:
```cmake
add_subdirectory(zf_queue)
```

Then add the following to CMakeLists.txt for each target that uses zf_queue:
```cmake
target_link_libraries(some_target_name zf_queue)
```

Include as usual:
```c
#include "zf_queue.h"
```

### Installation

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

Why zf?
--------

It stands for Ze Foundation. "Ze" is like "The" but with french or german accent.
Mostly because zf_anything looks better than tf_anything.
