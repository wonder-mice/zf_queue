cmake_minimum_required(VERSION 3.1)

add_library(zf_test INTERFACE)
target_include_directories(zf_test INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Dummy target to add sources to IDE
add_custom_target(zf_test_include SOURCES zf_test.hpp)
