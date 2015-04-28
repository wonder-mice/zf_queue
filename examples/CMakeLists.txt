cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic-errors")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic-errors")

add_executable(slist_args_c slist_args.c)
target_link_libraries(slist_args_c zf_queue)

add_executable(slist_args_cpp slist_args.cpp)
target_link_libraries(slist_args_cpp zf_queue)

add_executable(tailq_c_vs_cpp tailq_c_vs_cpp.cpp)
target_link_libraries(tailq_c_vs_cpp zf_queue)

add_executable(tailq_subsets tailq_subsets.cpp)
target_link_libraries(tailq_subsets zf_queue)
