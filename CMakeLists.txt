cmake_minimum_required(VERSION 3.10)
project(panic C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

add_library(panic sources/panic.h sources/panic.c)

add_executable(main examples/main.c)
target_link_libraries(main PRIVATE panic)
target_include_directories(main PRIVATE sources)
