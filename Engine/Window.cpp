#include "Input.h"
#include "Window.h"
#include <CommCtrl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Window::Window(int32 width, int32 height, const char* title)
{
	if (glfwInit() == false)
	{
		printf("Failed to initialize GLAD");
		return;
	}

	glfwDefaultWindowHints();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetWindowPosCallback(m_window, PositionCallback);
	glfwSetWindowSizeCallback(m_window, SizeCallback);
	glfwSetWindowMaximizeCallback(m_window, MaximizeCallback);
	glfwSetWindowIconifyCallback(m_window, MinimizeCallback);
	glfwSetWindowFocusCallback(m_window, FocusCallback);
	glfwSetDropCallback(m_window, DropCallback);

	// Set input callback events
	glfwSetKeyCallback(m_window, Input::KeyCallback);
	glfwSetCharCallback(m_window, Input::CharCallback);
	glfwSetMouseButtonCallback(m_window, Input::MouseButtonCallback);
	glfwSetCursorPosCallback(m_window, Input::MouseCursorPosCallback);
	glfwSetScrollCallback(m_window, Input::MouseScrollCallback);
	glfwSetCursorEnterCallback(m_window, Input::CursorEnterCallback);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, width, height);
}

Window::~Window()
{
	Close();

	glfwDestroyWindow(m_window);

	glfwTerminate();
}

bool Window::ShouldClose() const
{
	bool shouldClose = glfwWindowShouldClose(m_window);
	return shouldClose;
}

bool Window::IsMinimized() const
{
	bool minimized = !IsMaximized();
	return minimized;
}

bool Window::IsMaximized() const
{
	bool maximized = glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) > 0;
	return maximized;
}

void Window::SetPosition(int32 x, int32 y)
{
	glfwSetWindowPos(m_window, x, y);
}

void Window::SetPosition(glm::ivec2 position)
{
	SetPosition(position.x, position.y);
}

void Window::SetWindowMonitor(uint8 monitor)
{
	int32 monitorCount = 0;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

	if (monitor >= 0 && monitor <= monitorCount)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(monitors[monitor]);

		glfwSetWindowMonitor(m_window, monitors[monitor], 0, 0, mode->width, mode->height, mode->refreshRate);
	}
}

void Window::SetSize(int32 width, int32 height)
{
	glfwSetWindowSize(m_window, width, height);
	glViewport(0, 0, width, height);
}

void Window::SetSize(glm::ivec2 size)
{
	SetSize(size.x, size.y);
}

void Window::SetTitle(const char* title)
{
	glfwSetWindowTitle(m_window, title);
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_window, true);
}

void Window::ToggleFullscreen()
{
	if (IsFullScreen())
	{
		// glfwSetWindowMonitor(m_window, NULL, m_position.x, m_position.y, m_size.x, m_size.y, 0);
	}
	else
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
}

void Window::Maximise()
{
	glfwMaximizeWindow(m_window);
}

void Window::Minimize()
{
	glfwIconifyWindow(m_window);
}

void Window::Restore()
{
	glfwRestoreWindow(m_window);
}

bool Window::IsFullScreen() const
{
	return glfwGetWindowMonitor(m_window) != NULL;
}

int32 Window::GetWidth() const
{
	return GetSize().x;
}

int32 Window::GetHeight() const
{
	return GetSize().y;
}

glm::ivec2 Window::GetSize() const
{
	glm::ivec2 size = glm::ivec2(0);
	glfwGetWindowSize(m_window, &size.x, &size.y);
	return size;
}

float Window::GetAspectRatio() const
{
	int width = GetWidth();
	int height = GetHeight();
	float ratio = (float)width / (float)height;

	if (std::isnan(ratio) ||
		std::isinf(ratio))
	{
		ratio = 0.0f;
	}

	return ratio;
}

glm::ivec2 Window::GetPosition() const
{
	glm::ivec2 size = glm::ivec2(0);
	glfwGetWindowPos(m_window, &size.x, &size.y);
	return size;
}

void* Window::GetHandle() const
{
	return m_window;
}

void Window::PositionCallback(GLFWwindow* glfwWindow, int32 x, int32 y)
{
	REFERENCE(x);
	REFERENCE(y);

	Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
	glm::vec2 windowSize = window->GetSize();
	if (window != NULL)
	{
		if (window->IsFullScreen() == false)
		{
			// window->SetPosition(x, y);
		}
	}
}

void Window::SizeCallback(GLFWwindow* glfwWindow, int32 width, int32 height)
{
	Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
	if (window != NULL)
	{
		if (window->IsFullScreen() == false)
		{
			glViewport(0, 0, width, height);
			// window->SetSize(width, height);
		}
	}
}

void Window::MaximizeCallback(GLFWwindow* glfwWindow, int32 UNUSED_PARAM(maximized))
{
	Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
	REFERENCE(window);
}

void Window::MinimizeCallback(GLFWwindow* glfwWindow, int32 UNUSED_PARAM(minimized))
{
	Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
	REFERENCE(window);
}

void Window::FocusCallback(GLFWwindow* glfwWindow, int32 UNUSED_PARAM(focused))
{
	Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
	REFERENCE(window);
}

void Window::DropCallback(GLFWwindow* UNUSED_PARAM(glfwWindow), int32 UNUSED_PARAM(count), const char** UNUSED_PARAM(paths))
{
}
