# Minimum version of CMake required to build this project
cmake_minimum_required( VERSION 3.5 )

# Set the C++ standard
set( CMAKE_CXX_FLAGS "-std=c++17" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

# Name of the project
project( ner-ternary VERSION 1.0.0 DESCRIPTION "ner ternary tree annotater" )

# include directories
find_package( Catch2 3 REQUIRED )
find_package( nlohmann_json 3 REQUIRED )
find_package( MPI REQUIRED )
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")

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
target_link_libraries( nerternary PRIVATE libsModule PRIVATE nlohmann_json::nlohmann_json MPI::MPI_CXX )
target_link_libraries( node-test PRIVATE libsModule PRIVATE Catch2::Catch2WithMain )
target_link_libraries( process-data-test PRIVATE libsModule PRIVATE Catch2::Catch2WithMain )

target_include_directories( libsModule PUBLIC . )
