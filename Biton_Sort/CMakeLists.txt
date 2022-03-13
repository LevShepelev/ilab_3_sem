cmake_minimum_required(VERSION 3.1)

project(Biton_Sort)

add_executable(
    Biton_Sort
    source/Biton_Sort.cpp
    include/Biton_Sort.hpp
)
find_package(OpenCL REQUIRED)
target_link_libraries(Biton_Sort OpenCL::OpenCL)

include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")
set(CMAKE_EXE_LINKER_FLAGS "-lOpenCL")


