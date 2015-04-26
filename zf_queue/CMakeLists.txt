cmake_minimum_required(VERSION 3.2)

# This CMakeLists.txt file intended for:
# - include by master ../CMakeLists.txt
# - embedding zf_queue library into other projects (see README.md)

# zf_queue target (required)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(zf_queue INTERFACE)
target_include_directories(zf_queue INTERFACE $<BUILD_INTERFACE:${HEADERS_DIR}>)

# install (optional)
if(ZF_QUEUE_CONFIGURE_INSTALL)
	if(NOT DEFINED INSTALL_INCLUDE_DIR)
		set(INSTALL_INCLUDE_DIR include)
	endif()
	install(TARGETS zf_queue EXPORT zf_queue
		INCLUDES DESTINATION ${INSTALL_INCLUDE_DIR})
	install(DIRECTORY ${HEADERS_DIR}/
		DESTINATION ${INSTALL_INCLUDE_DIR}
		FILES_MATCHING PATTERN "zf_*.h*")
endif()

# dummy target to add headers to IDE project (optional)
if(ZF_QUEUE_CONFIGURE_IDE_SOURCES)
	set(HEADERS zf_queue.h)
	add_custom_target(zf_queue_sources SOURCES ${HEADERS})
endif()
