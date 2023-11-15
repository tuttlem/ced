project(tests)

add_subdirectory(lib/googletest-1.14.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../src)

add_executable(Google_Tests_run src/cont/list.cpp)

# target_link_libraries(Google_Tests_run )
target_link_libraries(Google_Tests_run  gtest gtest_main ced)