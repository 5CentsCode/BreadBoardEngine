#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return;
	}
}

Window::~Window()
{
	Close();

	glfwDestroyWindow(m_window);

	glfwTerminate();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

bool Window::IsMinimized() const
{
	return !IsMaximized();
}

bool Window::IsMaximized() const
{
	return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) > 0;
}

void Window::SetPosition(int32 x, int32 y)
{
	m_position = glm::ivec2(x, y);
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
	m_size = glm::ivec2(width, height);
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
		glfwSetWindowMonitor(m_window, NULL, m_position.x, m_position.y, m_size.x, m_size.y, 0);
	}
	else
	{
		m_position = GetPosition();

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
	glm::ivec2 size;
	glfwGetWindowSize(m_window, &size.x, &size.y);
	return size;
}

glm::ivec2 Window::GetPosition() const
{
	glm::ivec2 size;
	glfwGetWindowPos(m_window, &size.x, &size.y);
	return size;
}

void* Window::GetHandle() const
{
	return m_window;
}

void Window::PositionCallback(GLFWwindow* glfwWindow, int32 x, int32 y)
{
	Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
	if (window != NULL)
	{
		if (window->IsFullScreen() == false)
		{
			window->SetPosition(x, y);
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
			window->SetSize(width, height);
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
