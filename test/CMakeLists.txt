cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic-errors")

add_executable(zf_queue_test test.cpp zf_test.hpp)
target_link_libraries(zf_queue_test zf_queue)
add_test(NAME zf_queue_test COMMAND zf_queue_test)
