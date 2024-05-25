cmake_minimum_required(VERSION 3.1)

set(sourceFiles
    "Main.cpp"
    "Typedefs.h"
    "Window.h" "Window.cpp"
  "Application.h" "Application.cpp")

add_executable(BBEngine WIN32 ${sourceFiles})
#add_library(Engine STATIC ${SOURCE_FILES})
target_link_libraries(BBEngine LINK_PRIVATE glfw glad)
target_link_libraries(BBEngine LINK_PUBLIC glm::glm)
target_include_directories(BBEngine PUBLIC . ../External)