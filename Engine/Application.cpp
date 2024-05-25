#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

void Application::Initialize(void)
{
}

void Application::Run(void)
{
	Window window = Window(800, 600, "Hello Window");

	while (window.ShouldClose() == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glfwSwapBuffers((GLFWwindow*)window.GetHandle());
		glfwPollEvents();
	}
}

void Application::Shutdown(void)
{
	glfwTerminate();
}
