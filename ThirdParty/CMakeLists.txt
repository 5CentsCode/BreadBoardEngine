cmake_minimum_required (VERSION 3.5.1)
project (Dear_ImGui)

set (IMGUI_SOURCE
	"imconfig.h"
	"imgui.h"
	"imgui_internal.h"
	"imstb_rectpack.h"
	"imstb_textedit.h"
	"imstb_truetype.h"

	"imgui.cpp"
	"imgui_demo.cpp"
	"imgui_draw.cpp"
	"imgui_tables.cpp"
	"imgui_widgets.cpp"
	
	"Backends/imgui_impl_glfw.h"
	"Backends/imgui_impl_glfw.cpp"
	"Backends/imgui_impl_opengl3.h"
	"Backends/imgui_impl_opengl3.cpp"
	"Backends/imgui_impl_opengl3_loader.h"
)
list(TRANSFORM IMGUI_SOURCE PREPEND "imgui/")

add_library(ImGui STATIC ${IMGUI_SOURCE})
target_link_libraries(ImGui PRIVATE glfw glad)
target_include_directories(ImGui PUBLIC imgui)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE "stb")