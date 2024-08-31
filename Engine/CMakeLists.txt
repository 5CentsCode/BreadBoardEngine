cmake_minimum_required(VERSION 3.1)

set(AppName "BBEngine")

set(componentFiles
    "Components/Camera.h" "Components/Camera.cpp"
    "Components/Transform.h" "Components/Transform.cpp"
    "Components/Light.h"
    "Components/MeshRenderer.h"
    "Components/RectTransform.h" "Components/RectTransform.cpp"
    "Components/Sprite.h"
)

set(systemFiles
    "Systems/EnttSystem.h"
    "Systems/RenderSystem.h" "Systems/RenderSystem.cpp"
  )

set(sourceFiles
    "Application.h" "Application.cpp"
    "ConsoleWindow.h" "ConsoleWindow.cpp"
    "KeyCodes.h"
    "Input.h" "Input.cpp"
    "Main.cpp"
    "Material.h"
    "Mesh.h" "Mesh.cpp"
    "Resource.h"
    "StaticRenderer.h" "StaticRenderer.cpp"
    "ResourceManager.h" "ResourceManager.cpp"
    "Shader.h" "Shader.cpp"
    "Typedefs.h"
    "Texture.h" "Texture.cpp"
    "Vertex.h"
    "VertexAttribute.h"
    "Window.h" "Window.cpp"
)

set(BreadBoardSource
    ${componentFiles}
    ${systemFiles}
    ${sourceFiles}
)

foreach( sourceFile IN ITEMS ${BreadBoardSource} )
	get_filename_component( sourceFilePath "${sourceFile}" PATH )
    string( REPLACE "${CMAKE_SOURCE_DIR}" "" relativeSourceFilePath "${sourceFilePath}" )
    string( REPLACE "/" "\\" relativeSourceFilePath "${relativeSourceFilePath}" )
    source_group( "${relativeSourceFilePath}" FILES "${sourceFile}" )
endforeach()

# add_executable(${AppName} WIN32
#     ${componentFiles}
#     ${systemFiles}
#     ${sourceFiles})
add_library(${AppName} STATIC ${BreadBoardSource})
#add_library(Engine STATIC ${SOURCE_FILES})

target_compile_definitions(${AppName} PRIVATE PROJECT_ASSET_PATH="${CMAKE_SOURCE_DIR}/Assets/")
target_include_directories(${AppName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${AppName} PRIVATE freetype glad glfw stb tinyobjloader)
target_link_libraries(${AppName} PUBLIC EnTT::EnTT glm::glm ImGui)