cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
# Build Debug by default (relevant only for tests in header-only library)
if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
endif()

project(zf_queue)

set(INSTALL_INCLUDE_DIR include CACHE PATH
	"Installation directory for header files")
set(INSTALL_CMAKE_DIR lib/cmake/zf_queue CACHE PATH
	"Installation directory for CMake files")

# zf_queue
add_subdirectory(zf_queue)

# install
export(EXPORT zf_queue)
install(EXPORT zf_queue
	DESTINATION ${INSTALL_CMAKE_DIR})
configure_file(zf_queue-config.cmake.in zf_queue-config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/zf_queue-config.cmake
	DESTINATION ${INSTALL_CMAKE_DIR})

# tests and examples
enable_testing()
add_subdirectory(test)
add_subdirectory(examples)

# tags
include(ctags)
add_ctags_files(zf_queue)
add_ctags_files(test)
add_ctags_files(examples)
