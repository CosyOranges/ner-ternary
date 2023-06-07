find_package( nlohmann_json 3 REQUIRED )

set(LIBRARY_NAME
    cli
)

set(LIBRARY_HEADERS_DIR
    include/${LIBRARY_NAME}
)

set(LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/cli.hpp
)

set(LIBRARY_SOURCE_DIR
    src
)

set(LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/annotater.cpp
    ${LIBRARY_SOURCE_DIR}/tsvCleaner.cpp
)

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCE}
)

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries( ${LIBRARY_NAME} PRIVATE nlohmann_json::nlohmann_json Boost::log )
target_link_libraries( ${LIBRARY_NAME} PRIVATE searchtree )
