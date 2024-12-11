cmake_minimum_required(VERSION 3.1)

set(AppName "Engine")

set(componentFiles
    "Components/Camera.h" "Components/Camera.cpp"
    "Components/Transform.h" "Components/Transform.cpp"
)

set(sourceFiles
    "Application.h" "Application.cpp"
    "ConsoleWindow.h" "ConsoleWindow.cpp"
    "Draw.h" "Draw.cpp"
    "KeyCodes.h"
    "Input.h" "Input.cpp"
    "Main.cpp"
    "Shader.h" "Shader.cpp"
    "Typedefs.h"
    "Window.h" "Window.cpp"
)

set(DataTypeFiles
    "DataType/Image.h" "DataType/Image.cpp"
    "DataType/Material.h" "DataType/Material.cpp"
    "DataType/Mesh.h" "DataType/Mesh.cpp"
    "DataType/Model.h" "DataType/Model.cpp"
    "DataType/Texture.h" "DataType/Texture.cpp"
)

set(EditorFiles
    "Editor/EditorCamera.h" "Editor/EditorCamera.cpp"
)

set(BreadBoardSource
    ${componentFiles}
    ${systemFiles}
    ${sourceFiles}
    ${EditorFiles}
    ${DataTypeFiles}
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