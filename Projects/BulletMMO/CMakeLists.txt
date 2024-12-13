cmake_minimum_required(VERSION 3.1)

set(AppName "BulletMMO")

set(sourceFiles
    "src/BulletMMOApp.h" "src/BulletMMOApp.cpp")

foreach( sourceFile IN ITEMS ${sourceFiles} )
	get_filename_component( sourceFilePath "${sourceFile}" PATH )
    string( REPLACE "${CMAKE_SOURCE_DIR}" "" relativeSourceFilePath "${sourceFilePath}" )
    string( REPLACE "/" "\\" relativeSourceFilePath "${relativeSourceFilePath}" )
    source_group( "${relativeSourceFilePath}" FILES "${sourceFile}" )
endforeach()

add_executable(${AppName} WIN32 ${sourceFiles})

target_include_directories(${AppName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${AppName} Engine)

add_custom_command(
    TARGET ${AppName} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ $<TARGET_FILE_DIR:${AppName}>/Assets/
)

add_custom_command(
    TARGET ${AppName} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ ${CMAKE_CURRENT_BINARY_DIR}/Assets/
)

