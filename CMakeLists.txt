cmake_minimum_required(VERSION 2.8)

project(euler)

# Library
set(SOURCES
    src/io.cpp
    src/conversions.cpp
    )
add_library(euler_conversions ${SOURCES})
target_include_directories(euler_conversions PUBLIC include)

# Application
add_executable(euler apps/euler.cpp)
target_link_libraries(euler euler_conversions)

# Testing
enable_testing()
set(TEST_SOURCES 
    test/catch/catch_main.cpp
    test/test_io.cpp
    test/test_conversions.cpp
    )
add_executable(run_all_tests ${TEST_SOURCES})
target_include_directories(run_all_tests PRIVATE test)
target_link_libraries(run_all_tests euler_conversions)
add_test(NAME AllTests COMMAND run_all_tests)
