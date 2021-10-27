cmake_minimum_required(VERSION 3.6)

project(HW-2)

# Flags to generate test coverage
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Make static task library
add_library(static_task STATIC project/static_task/src/task.c)
target_include_directories(static_task PUBLIC project/static_task/include)
target_link_libraries(static_task m)

# Find package for dynamic library
find_package(Threads REQUIRED)

# Make dynamic task library
add_library(dynamic_task SHARED project/dynamic_task/src/task.c)
target_include_directories(dynamic_task PUBLIC project/dynamic_task/include)
target_link_libraries(dynamic_task m Threads::Threads)

# Make menu library
add_library(menu STATIC project/menu/src/menu.c)
target_include_directories(menu PUBLIC project/menu/include)
target_link_libraries(menu dynamic_task)

# Make executable program
add_executable(main.out project/cmd/src/main.c)
target_include_directories(main.out PUBLIC project/menu/include)
target_link_libraries(main.out menu)

# Find package for test
find_package(GTest REQUIRED)

# Make executable test program
add_executable(test.out test/main.cpp)
target_link_libraries(test.out dynamic_task ${GTEST_LIBRARIES} Threads::Threads)
