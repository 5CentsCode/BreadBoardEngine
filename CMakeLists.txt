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

add_subdirectory(thirdparty/glad)
set_target_properties(glad PROPERTIES FOLDER thirdparty/glad)

add_subdirectory(thirdparty/glfw)
include_directories(thirdparty/glfw/include)
set_target_properties(glfw PROPERTIES FOLDER thirdparty/GLFW3)
set_target_properties(update_mappings PROPERTIES FOLDER thirdparty/GLFW3)

add_subdirectory(thirdparty/glm)
set_target_properties(glm PROPERTIES FOLDER thirdparty/glm)

if(MSVC)
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

add_subdirectory(Engine)

if(MSVC)
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BBEngine)
    endif()
endif()