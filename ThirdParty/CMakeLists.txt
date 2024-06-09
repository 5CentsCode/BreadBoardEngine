cmake_minimum_required (VERSION 3.5.1)
project (Dear_ImGui)

set (imgui_headers imconfig.h imgui.h imgui_internal.h imstb_rectpack.h imstb_textedit.h imstb_truetype.h)
set (imgui_sources imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp)
set (backend_sources Backends/imgui_impl_glfw.h Backends/imgui_impl_glfw.cpp Backends/imgui_impl_opengl3.h Backends/imgui_impl_opengl3.cpp Backends/imgui_impl_opengl3_loader.h)

list(TRANSFORM imgui_headers PREPEND "imgui/")
list(TRANSFORM imgui_sources PREPEND "imgui/")
list(TRANSFORM backend_sources PREPEND "imgui/")

add_library(ImGui STATIC ${imgui_sources} ${imgui_headers} ${backend_sources})
target_link_libraries(ImGui PRIVATE glfw glad)
target_include_directories(ImGui PUBLIC imgui)