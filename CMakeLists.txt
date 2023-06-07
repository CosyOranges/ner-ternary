# Minimum version of CMake required to build this project
cmake_minimum_required( VERSION 3.15 )

# Set the C++ standard
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
set( CMAKE_CXX_FLAGS "-std=c++17" )

# Name of the project
project( ner-ternary VERSION 1.0.0 DESCRIPTION "ner ternary tree annotater" )

add_subdirectory(proto)
add_subdirectory(server)
add_subdirectory(client)
# add_subdirectory(client/libs/cli)
