cmake_minimum_required(VERSION 3.1)

add_library(zf_queue INTERFACE)
target_include_directories(zf_queue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Dummy target to add sources to IDE
add_custom_target(zf_queue_sources SOURCES zf_queue.hpp zf_queue.h)
