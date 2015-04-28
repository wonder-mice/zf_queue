zf_queue
========

### Intrusive lists library

This is a blend of classic BSD [sys/queue.h] design with Linux [linux/list.h]
implementation. BSD implementation has a nice variety of primitives (list,
slist, tailq, stailq), but it uses macros. Linux implementation less reach and
has GPL license, but uses functions (more type safety, better error messages)
and has some interesting optimizations. This library tries to take the best from
both and mix it under BSD-style license. In addition to C implementation, it
also provides binary compatible C++ interface.

[sys/queue.h]: https://svnweb.freebsd.org/base/head/sys/sys/queue.h
[linux/list.h]: https://github.com/torvalds/linux/blob/master/include/linux/list.h

### Why intrusive?

In short, intrusive lists:

* provide better data locality
* allow to do less memory allocations
* therefore have better performance

For more details read:

* [Intrusive and non-intrusive containers](http://www.boost.org/doc/libs/1_57_0/doc/html/intrusive/intrusive_vs_nontrusive.html)
* [Performance comparison](http://www.boost.org/doc/libs/1_57_0/doc/html/intrusive/performance.html)

Usage
--------

This is a header-only library. It contains single header file
[zf_queue.h](zf_queue/zf_queue.h).

### Embedding

Put [zf_queue.h](zf_queue/zf_queue.h) into your source tree.
Include as usual:

```c
#include <zf_queue.h>
```

### Embedding with CMake

Put [zf_queue](zf_queue) directory into your source tree.
In CMakeLists.txt inside parent directory add:

```cmake
add_subdirectory(zf_queue)
```

For each target that uses zf_queue in corresponding CMakeLists.txt file add:

```cmake
target_link_libraries(my_target zf_queue)
```

Include as usual:

```c
#include <zf_queue.h>
```

### Installation

```bash
git clone https://github.com/wonder-mice/zf_queue.git zf_queue.git
mkdir zf_queue.build && cd zf_queue.build
cmake ../zf_queue.git -DCMAKE_INSTALL_PREFIX=/usr/local
make && make install
```

This will also install
`${CMAKE_INSTALL_PREFIX}/lib/cmake/zf_queue/zf_queue.cmake`
and
`${CMAKE_INSTALL_PREFIX}/lib/cmake/zf_queue/zf_queue-config.cmake`.
The first one is for direct `include` from CMakeLists.txt file.
The second can be located by CMake with:

```cmake
find_package(zf_queue)
```

Both will add `zf_queue` imported interface library target.
For each target that uses zf_queue in corresponding CMakeLists.txt file add:

```cmake
target_link_libraries(my_target zf_queue)
```

### Versioning

It's recommended to define `ZF_QUEUE_VERSION_REQUIRED` to current value of
`ZF_QUEUE_VERSION` before [zf_queue.h](zf_queue/zf_queue.h) include:

```c
#define ZF_QUEUE_VERSION_REQUIRED 1
#include <zf_queue.h>
```

For each non-compatible change `ZF_QUEUE_VERSION` will be incremented. If
code defines `ZF_QUEUE_VERSION_REQUIRED` compilation will break when those
numbers do not match.

Examples
--------

Below is a list of examples:

* [slist_args.c](examples/slist_args.c) - singly-linked list in C
* [slist_args.cpp](examples/slist_args.cpp) - singly-linked list in C++
* [tailq_c_vs_cpp](examples/tailq_c_vs_cpp.cpp) - tail queue C and C++
  interface comparison
* [tailq_subsets](examples/tailq_subsets.cpp) - tail queue for generating subsets

C++ and C interfaces are almost identical, the main difference is that C++
interface operates in terms of entries instead of nodes. Consider:
```c++
typedef struct line_t
{
    zf_tailq_node node;
}
line_t;
// Declaration with C interface
zf_tailq_head line_list;
// Declaration with C++ interface
zf_tailq_head_<line_t, &line_t::node> line_list;
// Declaration for both C and C++, in C source files will expand to
//     zf_tailq_head line_list;
// and in C++ source files will expand to
//     zf_tailq_head_<line_t, &line_t::node> line_list;
zf_tailq_head_t(line_t, node) line_list;

line_t aline;

// Add item with C interface
zf_tailq_insert_head(&line_list, &aline.node);
// Add item with C++ interface
zf_tailq_insert_head_(&line_list, &aline);

// Get item with C interface
zf_entry(zf_tailq_last(&line_list), line_t, node);
// Get item with C++ interface
zf_tailq_last_(&line_list);
```

Why zf?
--------

It stands for Ze Foundation. "Ze" is like "The" but with french or german accent.
Mostly because zf_anything looks better than tf_anything.
