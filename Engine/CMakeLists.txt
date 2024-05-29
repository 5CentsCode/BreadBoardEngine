cmake_minimum_required(VERSION 3.1)

set(AppName "BBEngine")

set(sourceFiles
    "Application.h" "Application.cpp"
    "ConsoleWindow.h" "ConsoleWindow.cpp"
    "Main.cpp"
    "Resource.h"
    "ResourceManager.h" "ResourceManager.cpp"
    "Shader.h" "Shader.cpp"
    "Typedefs.h"
    "VertexAttribute.h"
    "Window.h" "Window.cpp" "Components/Camera.h" "Components/Camera.cpp" "Components/Transform.h" "Components/Transform.cpp")

add_executable(${AppName} WIN32 ${sourceFiles})
#add_library(Engine STATIC ${SOURCE_FILES})

#set_source_files_properties(${AppName} PROPERTIES )
target_compile_definitions(${AppName} PRIVATE PROJECT_ASSET_PATH="${CMAKE_SOURCE_DIR}/Assets/")

target_link_libraries(${AppName} LINK_PRIVATE glfw glad)
target_link_libraries(${AppName} LINK_PUBLIC glm::glm)
target_include_directories(${AppName} PUBLIC . ../External)