# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.5)

# Set the C++ standard
SET(CMAKE_CXX_FLAGS "-std=c++17")

# Name of the project
project(ner-ternary VERSION 1.0.0 DESCRIPTION "ner ternary tree annotater")

# include directories
include_directories("/usr/local/Cellar/nlohmann-json/3.10.5/include")
find_package(Catch2 3 REQUIRED)

# Declare a new library target.
add_library(
    libsModule

    SHARED

    lib/node.cpp
    lib/processData.cpp
)

add_library( nlohmann_json INTERFACE )

# Add all the source files needed to build the executable
add_executable(
    nerternary

    src/main.cpp
)

add_executable(
    test

    test/test.cpp
)

target_link_libraries(nerternary libsModule)
target_link_libraries(test PRIVATE libsModule PRIVATE Catch2::Catch2WithMain)

target_include_directories(libsModule PUBLIC .)
