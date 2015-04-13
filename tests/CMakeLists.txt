cmake_minimum_required(VERSION 3.2)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -pedantic-errors")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Werror -pedantic-errors")
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
	add_executable(${target} ${ARGN} zf_queue_tests.h)
	target_link_libraries(${target} zf_queue zf_test)
	add_test(NAME ${target} COMMAND ${target})
endfunction()

add_zf_queue_test(zf_queue_c_tests zf_queue_c_tests.c)
add_zf_queue_test(zf_queue_cpp_tests zf_queue_cpp_tests.cpp)
#add_executable(zf_queue_cpp_tests zf_queue_cpp_tests.cpp zf_queue_tests.h)
#target_link_libraries(zf_queue_cpp_tests zf_queue zf_test)
#add_test(NAME zf_queue_cpp_tests COMMAND zf_queue_cpp_tests)
