cmake_minimum_required(VERSION 3.1)

# так пишутся комментарии

project(AVL_tree)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/../Test"
    "Test"   
)
add_executable(
    test_tree
    Google_test/test_tree.cpp
)

add_executable(
    AVL_tree
    source/AVL_tree.cpp
    includes/AVL_tree.h
)


target_include_directories(
    test_tree PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


target_link_libraries(
    test_tree PRIVATE
    gtest gtest_main   
)

include_directories(includes)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")


