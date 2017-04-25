cmake_minimum_required(VERSION 2.8)

project(euler)

# Find Eigen
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(Eigen3 REQUIRED)

# Library
set(SOURCES
    src/io.cpp
    src/rotations.cpp
    )
add_library(euler_rotations ${SOURCES})
target_include_directories(euler_rotations PUBLIC 
    include
    ${EIGEN3_INCLUDE_DIR}
    )

# Application
add_executable(euler apps/euler.cpp)
target_link_libraries(euler euler_rotations)

# Testing
enable_testing()
set(TEST_SOURCES 
    test/catch/catch_main.cpp
    test/test_io.cpp
    test/test_rotations.cpp
    )
add_executable(run_all_tests ${TEST_SOURCES})
target_include_directories(run_all_tests PRIVATE test)
target_link_libraries(run_all_tests euler_rotations)
add_test(NAME AllTests COMMAND run_all_tests)
