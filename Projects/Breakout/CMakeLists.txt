cmake_minimum_required(VERSION 3.1)

set(AppName "Breakout")

set(sourceFiles
    "src/BreakoutApp.h" "src/BreakoutApp.cpp"
    "src/Brick.h"
    "src/GameLevel.h"
    "src/GameState.h" "src/GameLevel.cpp"
    "src/Paddle.h"
    "src/Ball.h"
    "src/PaddleSystem.h" "src/PaddleSystem.cpp")

foreach( sourceFile IN ITEMS ${sourceFiles} )
	get_filename_component( sourceFilePath "${sourceFile}" PATH )
    string( REPLACE "${CMAKE_SOURCE_DIR}" "" relativeSourceFilePath "${sourceFilePath}" )
    string( REPLACE "/" "\\" relativeSourceFilePath "${relativeSourceFilePath}" )
    source_group( "${relativeSourceFilePath}" FILES "${sourceFile}" )
endforeach()

add_executable(${AppName} WIN32 ${sourceFiles})

target_compile_definitions(${AppName} PRIVATE PROJECT_ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
target_include_directories(${AppName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${AppName} BBEngine)