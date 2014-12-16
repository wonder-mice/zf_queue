cmake_minimum_required(VERSION 3.1)

add_subdirectory(zf_test)
add_subdirectory(main)

add_test(NAME main COMMAND test-main)
