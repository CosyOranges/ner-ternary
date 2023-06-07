    set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(LIBRARY_NAME
    searchtree
)
#
# Protobuf/Grpc source files
#
set(PROTO_FILES
    SearchTree/searchtree.proto
)

#
# Add Library target with protobuf sources
#
add_library(${LIBRARY_NAME} STATIC ${PROTO_FILES})
target_link_libraries(searchtree
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
        gRPC::grpc++_reflection
)
target_include_directories(searchtree PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

#
# Compile protobuf and grpc files in myproto target to cpp
#
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET searchtree LANGUAGE cpp)
protobuf_generate(TARGET searchtree LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
