#
#   Dependencies
#
find_package( Catch2 3 REQUIRED )
find_package( nlohmann_json 3 REQUIRED )
add_definitions( -DBOOST_LOG_DYN_LINK )
find_package( Boost 1.80.0 COMPONENTS log REQUIRED )
find_package( protobuf CONFIG REQUIRED )
find_package( gRPC CONFIG REQUIRED )

#
#   Shared Library
#
add_library(
    node_lib

    SHARED

    lib/node.cpp
    lib/processor.cpp
)

#
#   Sources
#
set(
    SOURCES
    src/main.cpp
)

#
#   Tests
#
add_executable(
    unit-test
    tests/node_test.cpp
    tests/processor_test.cpp
)

#
#   Server
#
add_executable(
    server
    ${SOURCES}
)

#
#   Linking Libraries with executables
#
target_link_libraries( node_lib PRIVATE nlohmann_json::nlohmann_json Boost::log)
target_link_libraries( server PRIVATE node_lib PRIVATE nlohmann_json::nlohmann_json Boost::log gRPC::grpc++_reflection )
target_link_libraries( server PRIVATE searchtree )
target_link_libraries( unit-test PRIVATE node_lib nlohmann_json::nlohmann_json Boost::log Catch2::Catch2WithMain )

target_include_directories( node_lib PUBLIC . )
