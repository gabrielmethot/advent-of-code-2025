cmake_minimum_required(VERSION 4.0)

if ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    add_compile_options("-Wall" "-Wextra")
endif ()

project("advent_of_code_2025")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Used by language servers (e.g., clangd) to generate autocomplete data

add_executable(day1_part1 day1/part1.cpp)
add_executable(day1_part2 day1/part2.cpp)
add_executable(day2_part1 day2/part1.cpp)