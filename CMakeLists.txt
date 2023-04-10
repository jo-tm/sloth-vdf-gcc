cmake_minimum_required(VERSION 3.10)

project(sloth_permutation_example C)

set(CMAKE_C_STANDARD 99)

# Find the GMP library
find_library(GMP_LIBRARY gmp)

if (NOT GMP_LIBRARY)
    message(FATAL_ERROR "GMP library not found")
endif ()

# Include the GMP header files
find_path(GMP_INCLUDE_DIR gmp.h)

if (NOT GMP_INCLUDE_DIR)
    message(FATAL_ERROR "GMP header files not found")
endif ()

include_directories(${GMP_INCLUDE_DIR})

add_executable(sloth_permutation_example main.c sloth_permutation.c)

# Link the GMP library
target_link_libraries(sloth_permutation_example ${GMP_LIBRARY})

# Testing
#enable_testing()

#add_executable(test_sloth_permutation test_sloth_permutation.c)
#target_link_libraries(test_sloth_permutation sloth_permutation ${GMP_LIBRARY})

#add_test(NAME test_sloth_permutation COMMAND test_sloth_permutation)

