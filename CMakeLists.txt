cmake_minimum_required(VERSION 2.8)

project(euler)

# use C++11
set(CMAKE_CXX_FLAGS "-std=c++11")

# Library
set(SOURCES
    src/io.cpp
    src/rotations.cpp
    )
add_library(euler_rotations ${SOURCES})
target_include_directories(euler_rotations PUBLIC 
    include
    )

# Application
add_executable(euler apps/euler.cpp)
target_link_libraries(euler euler_rotations)

# Install
install(TARGETS euler DESTINATION bin)

# Testing
enable_testing()

add_executable(test_io test/test_io.cpp test/catch/catch_main.cpp)
target_include_directories(test_io PRIVATE test)
target_link_libraries(test_io euler_rotations)
add_test(NAME test_io COMMAND test_io)

add_executable(test_rotations test/test_rotations.cpp test/catch/catch_main.cpp)
target_include_directories(test_rotations PRIVATE test)
target_link_libraries(test_rotations euler_rotations)
add_test(NAME test_rotations COMMAND test_rotations)
