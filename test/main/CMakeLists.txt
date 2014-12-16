cmake_minimum_required(VERSION 3.1)

add_executable(test-main
	main.cpp)
target_link_libraries(test-main zf_queue zf_test)
