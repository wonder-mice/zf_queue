cmake_minimum_required(VERSION 3.2)

# zf_queue target (required)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(zf_queue INTERFACE)
target_include_directories(zf_queue INTERFACE $<BUILD_INTERFACE:${HEADERS_DIR}>)

# install (optional)
if(NOT ZF_QUEUE_NO_INSTALL)
	if(NOT DEFINED INSTALL_INCLUDE_DIR)
		set(INSTALL_INCLUDE_DIR include)
	endif()
	install(TARGETS zf_queue EXPORT zf_queue
		INCLUDES DESTINATION ${INSTALL_INCLUDE_DIR})
	install(DIRECTORY ${HEADERS_DIR}/
		DESTINATION ${INSTALL_INCLUDE_DIR}
		FILES_MATCHING PATTERN "zf_*.h*")
endif()

# dummy target to add headers to IDE files tree (optional)
if(NOT ZF_QUEUE_NO_SOURCES)
	set(HEADERS
		zf_queue.h
		zf_queue.hpp)
	add_custom_target(zf_queue_headers SOURCES ${HEADERS})
endif()
