# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Set the C++ standard
SET(CMAKE_CXX_FLAGS "-std=c++17")

# Create a variable for all src files
file(GLOB HELPERS
    header-folder/*.h
    src/lib/*.cpp
)

# Name of the project
project(nerternary)

# include directories
include_directories("/usr/local/Cellar/nlohmann-json/3.10.5/include")

# Add all the source files needed to build the executable
add_executable(nerternary src/main.cpp ${HELPERS})

# Include the directory where MyLibrary project is. Otherwise, we can't use the
# library
# add_subdirectory(libraries/MyLibrary)

# Link the executable and the library together
# target_link_libraries(Project MyLibrary)