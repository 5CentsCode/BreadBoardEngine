cmake_minimum_required(VERSION 3.1)

project(BreadBoard)
set(USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Prevent "warning D9025 : overriding '/W3' with '/W4'"
string(REGEX REPLACE "/W[1-3]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLAD_GL)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(ThirdParty)
set_target_properties(ImGui PROPERTIES FOLDER ThirdParty/ImGui)
set_target_properties(stb PROPERTIES FOLDER ThirdParty/stb)

add_subdirectory(ThirdParty/entt)

add_subdirectory(ThirdParty/freetype)
set_target_properties(freetype PROPERTIES FOLDER ThirdParty/freetype)
target_compile_options(freetype PRIVATE
    "/wd4267;" # disable "unknown pragma 'mark'" warnings
)

add_subdirectory(ThirdParty/glad)
set_target_properties(glad PROPERTIES FOLDER ThirdParty/glad)

add_subdirectory(ThirdParty/glfw)
# include_directories(ThirdParty/glfw/include)
set_target_properties(glfw PROPERTIES FOLDER ThirdParty/GLFW3)
set_target_properties(update_mappings PROPERTIES FOLDER ThirdParty/GLFW3)

add_subdirectory(ThirdParty/glm)
set_target_properties(glm PROPERTIES FOLDER ThirdParty/glm)

add_subdirectory(ThirdParty/tinyobjloader)
set_target_properties(tinyobjloader PROPERTIES FOLDER ThirdParty/tinyobjloader)
set_target_properties(uninstall PROPERTIES FOLDER ThirdParty/tinyobjloader)

if(MSVC)
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

add_subdirectory(Engine)
add_subdirectory(Projects)

if(MSVC)
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Engine)
    endif()
endif()