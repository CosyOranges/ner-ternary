# Minimum version of CMake required to build this project
cmake_minimum_required( VERSION 3.5 )

# Set the C++ standard
SET( CMAKE_CXX_FLAGS "-std=c++17" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

# Name of the project
project( ner-ternary VERSION 1.0.0 DESCRIPTION "ner ternary tree annotater" )

include(FetchContent)

# include directories
find_package( Catch2 3 REQUIRED )
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

# Declare a new library target.
add_library(
    libsModule

    SHARED

    lib/node.cpp
    lib/processData.cpp
)

# Add all the source files needed to build the executable
add_executable(
    nerternary

    src/main.cpp
)

# TESTING executables
add_executable(
    node-test

    tests/node_test.cpp
)

add_executable(
    process-data-test

    tests/process_data_test.cpp
)

# Linking
target_link_libraries( libsModule PRIVATE nlohmann_json::nlohmann_json )
target_link_libraries( nerternary PRIVATE libsModule )
target_link_libraries( node-test PRIVATE libsModule PRIVATE Catch2::Catch2WithMain )
target_link_libraries( process-data-test PRIVATE libsModule PRIVATE Catch2::Catch2WithMain )

target_include_directories( libsModule PUBLIC . )
