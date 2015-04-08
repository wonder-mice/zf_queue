zf_queue
========

This is a blend of classic BSD [sys/queue.h] design with Linux [linux/list.h]
implementation. BSD implementation has a nice variety of primitives (list,
slist, tailq, stailq), but it uses macros. Linux implementation less reach and
has GPL license, but uses functions (more type safety, better error messages)
and has some interesting optimizations. This library tries to take the best from
both and mix it under BSD-style license. In addition to C implementation, it
also provides binary compatible C++ interface.

[sys/queue.h]: https://svnweb.freebsd.org/base/head/sys/sys/queue.h
[linux/list.h]: https://github.com/torvalds/linux/blob/master/include/linux/list.h

Usage
--------

This is a header-only library. It contains single header file
[zf_queue.h](zf_queue/zf_queue.h).

### Embedding

Put [zf_queue.h](zf_queue/zf_queue.h) into your source tree.
Include as usual:

```c
#include "zf_queue.h"
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
#include "zf_queue.h"
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

Examples
--------

Below is a list of examples:

* [slist_args.c](test/example/slist_args.c) - singly-linked list in C
* [slist_args.cpp](test/example/slist_args.cpp) - singly-linked list in C++


Why zf?
--------

It stands for Ze Foundation. "Ze" is like "The" but with french or german accent.
Mostly because zf_anything looks better than tf_anything.
