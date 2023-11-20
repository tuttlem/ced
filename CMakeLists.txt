cmake_minimum_required(VERSION 3.22.1)
project(ced C)

set(CMAKE_C_STANDARD 11)

add_library(ced
    src/cont/list.c
    src/cont/stack.c
    src/cont/queue.c
    src/cont/btree.c
    src/cont/types.c
    src/util/log.c)

add_subdirectory(tests)