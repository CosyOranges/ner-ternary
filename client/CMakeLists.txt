#
#   Dependencies
#
find_package( Catch2 3 REQUIRED )
find_package( nlohmann_json 3 REQUIRED )
add_definitions( -DBOOST_LOG_DYN_LINK )
find_package( Boost 1.80.0 COMPONENTS log REQUIRED )

#
# Sources
#
set(SOURCES
    src/main.cpp
)

set(CLI_LIBRARIES
    cli
)
set(CLI_LIBRARIES_DIR
    libs
)

# add_subdirectory(libs/cli)

set(CLI_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/client/src/cli/include)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

set_source_files_properties(${SOURCES} PROPERTIES COMPILE_OPTIONS "-Wall;-Werror")
#
# Target
#
add_executable(treecli ${SOURCES})

foreach(LIBRARY ${CLI_LIBRARIES})
    add_subdirectory("${CLI_LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)
target_link_libraries( treecli PRIVATE ${CLI_LIBRARIES} nlohmann_json::nlohmann_json Boost::log )
target_link_libraries( treecli PRIVATE searchtree )
