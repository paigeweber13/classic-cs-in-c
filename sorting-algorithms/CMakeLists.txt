cmake_minimum_required(VERSION 3.16)
project(sorting_algorithms C)

set(CMAKE_C_STANDARD 99)
set(GCC_COMPILE_FLAGS -O3)
#set(GCC_COMPILE_FLAGS -O3 -march=native -mtune=native)

add_executable(sorting_algorithms src/main.c src/utils.c src/utils.h src/sort-algorithms.c src/sort-algorithms.h src/test.c src/test.h)

target_compile_options(sorting_algorithms PRIVATE -O3 -march=native -mtune=native)
target_link_libraries(sorting_algorithms m)

