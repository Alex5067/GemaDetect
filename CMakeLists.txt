cmake_minimum_required(VERSION 3.14)

project("sample")

add_subdirectory(lib)
add_executable(main main.cpp)
target_link_libraries(main PUBLIC Neu)

