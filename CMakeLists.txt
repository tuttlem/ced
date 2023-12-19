cmake_minimum_required(VERSION 3.22.1)
project(ced C)

set(CMAKE_C_STANDARD 11)

add_library(ced
    src/mem/buffer.c
    src/net/server.c
    src/util/hash.h
    src/cont/list.c
    src/cont/stack.c
    src/cont/queue.c
    src/cont/btree.c
    src/cont/data_cmp.c
    src/cont/graph.c
    src/cont/htable.c
    src/util/log.c
    src/util/hash.c
    src/util/base64.c
    src/util/event.c
    src/var/variant.c)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(tests)
endif()
