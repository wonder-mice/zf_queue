cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -pedantic-errors")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Werror -pedantic-errors")

add_executable(test_zf_queue_cpp zf_test.hpp test_zf_queue.h test_zf_queue.cpp)
target_link_libraries(test_zf_queue_cpp zf_queue)
add_test(NAME test_zf_queue_cpp COMMAND test_zf_queue_cpp)
