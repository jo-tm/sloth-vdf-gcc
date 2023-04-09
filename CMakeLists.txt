cmake_minimum_required(VERSION 3.10)
project(sloth_permutation C)

set(CMAKE_C_STANDARD 99)

add_library(sloth_permutation sloth_permutation.c)

add_executable(sloth_permutation_example main.c)
target_link_libraries(sloth_permutation_example sloth_permutation)
