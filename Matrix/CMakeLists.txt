cmake_minimum_required(VERSION 3.1)

# так пишутся комментарии

project(Matrix)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/../Test"
    "Test"   
)
add_executable(
    test_matrix
    Google_test/test_matrix.cpp
)

add_executable(
    Matrix
    source/Matrix.cpp
    include/Matrix.h
)

add_executable(
    Test_maker
    Tests/Test_maker.cpp
)

target_include_directories(
    test_matrix PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_link_libraries(
    test_matrix PRIVATE
    gtest gtest_main   
)

include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")


