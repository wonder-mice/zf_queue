cmake_minimum_required(VERSION 3.2)

include(CMakeParseArguments)

# common flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic-errors")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic-errors")

# zf_test
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(zf_test INTERFACE)
target_include_directories(zf_test INTERFACE $<BUILD_INTERFACE:${HEADERS_DIR}>)
set(HEADERS zf_test.h zf_test.hpp)
add_custom_target(zf_test_headers SOURCES ${HEADERS})

function(add_zf_queue_test target)
	cmake_parse_arguments(arg
		""
		""
		"SOURCES;FLAGS"
		${ARGN})
	add_executable(${target} ${arg_SOURCES} zf_queue_tests.h)
	set_target_properties(${target} PROPERTIES COMPILE_FLAGS "${arg_FLAGS}")
	target_link_libraries(${target} zf_queue zf_test)
	add_test(NAME ${target} COMMAND ${target})
endfunction()

add_zf_queue_test(zf_queue_c_tests
	SOURCES zf_queue_c_tests.c
	FLAGS -std=c99)
add_zf_queue_test(zf_queue_c11_tests
	SOURCES zf_queue_c11_tests.c
	FLAGS -std=c11)
add_zf_queue_test(zf_queue_cpp_tests
	SOURCES zf_queue_cpp_tests.cpp
	FLAGS -std=c++03)
add_zf_queue_test(zf_queue_cpp11_tests
	SOURCES zf_queue_cpp11_tests.cpp
	FLAGS -std=c++11)
add_zf_queue_test(zf_queue_cpp14_tests
	SOURCES zf_queue_cpp14_tests.cpp
	FLAGS -std=c++14)
