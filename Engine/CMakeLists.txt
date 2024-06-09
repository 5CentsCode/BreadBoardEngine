cmake_minimum_required(VERSION 3.1)

set(AppName "BBEngine")

set(sourceFiles
    "Application.h" "Application.cpp"
    "ConsoleWindow.h" "ConsoleWindow.cpp"
    "Main.cpp"
    "Mesh.h" "Mesh.cpp"
    "Resource.h"
    "ResourceManager.h" "ResourceManager.cpp"
    "Shader.h" "Shader.cpp"
    "Typedefs.h"
    "Vertex.h"
    "VertexAttribute.h"
    "Window.h" "Window.cpp"
    
    "Components/Camera.h" "Components/Camera.cpp"
    "Components/Transform.h" "Components/Transform.cpp"
)

foreach( sourceFile IN ITEMS ${BreadBoardSource} )
	get_filename_component( sourceFilePath "${sourceFile}" PATH )
    string( REPLACE "${CMAKE_SOURCE_DIR}" "" relativeSourceFilePath "${sourceFilePath}" )
    string( REPLACE "/" "\\" relativeSourceFilePath "${relativeSourceFilePath}" )
    source_group( "${relativeSourceFilePath}" FILES "${sourceFile}" )
endforeach()

add_executable(${AppName} WIN32 ${sourceFiles})
#add_library(Engine STATIC ${SOURCE_FILES})

target_compile_definitions(${AppName} PRIVATE PROJECT_ASSET_PATH="${CMAKE_SOURCE_DIR}/Assets/")
target_include_directories(${AppName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${AppName} LINK_PRIVATE glfw glad freetype tinyobjloader)
target_link_libraries(${AppName} LINK_PUBLIC EnTT::EnTT glm::glm ImGui)