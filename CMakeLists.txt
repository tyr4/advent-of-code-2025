cmake_minimum_required(VERSION 4.0)
project(advent_of_code_2025 C)

set(CMAKE_C_STANDARD 11)

#add_executable(advent_of_code_2025 day1.c)
#add_executable(advent_of_code_2025 day2.c)
add_executable(advent_of_code_2025 day3.c)

# link the math library because linux moment
target_link_libraries(advent_of_code_2025 m)
