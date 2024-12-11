cmake_minimum_required(VERSION 3.1)

set(AppName "Tetris")

set(sourceFiles
    "src/TetrisApp.h" "src/TetrisApp.cpp")

foreach( sourceFile IN ITEMS ${sourceFiles} )
	get_filename_component( sourceFilePath "${sourceFile}" PATH )
    string( REPLACE "${CMAKE_SOURCE_DIR}" "" relativeSourceFilePath "${sourceFilePath}" )
    string( REPLACE "/" "\\" relativeSourceFilePath "${relativeSourceFilePath}" )
    source_group( "${relativeSourceFilePath}" FILES "${sourceFile}" )
endforeach()

add_executable(${AppName} WIN32 ${sourceFiles})

target_compile_definitions(${AppName} PRIVATE PROJECT_ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
target_include_directories(${AppName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${AppName} Engine)