cmake_minimum_required(VERSION 3.17)
project(sorting_algorithms C)

set(CMAKE_C_STANDARD 99)

add_executable(sorting_algorithms src/main.c src/utils.c src/utils.h src/sort-algorithms.c src/sort-algorithms.h src/test.c src/test.h)
target_link_libraries(sorting_algorithms m)
