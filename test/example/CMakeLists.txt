cmake_minimum_required(VERSION 3.2)

add_executable(slist_args_c slist_args.c)
target_link_libraries(slist_args_c zf_queue)

add_executable(slist_args_cpp slist_args.cpp)
target_link_libraries(slist_args_cpp zf_queue)
