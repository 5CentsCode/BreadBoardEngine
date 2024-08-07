#include "Application.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.h"

Application::Application()
{
	m_previousTime = 0.0f;
}

Application::~Application()
{
}

void Application::InternalInitialize(void)
{
	m_window = std::make_unique<Window>(800, 600, "Hello Window");

	Initialize();
}

void Application::InternalRun(void)
{
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (m_window->ShouldClose() == false)
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		Input::PollInputEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		Update(deltaTime);

		glfwSwapBuffers((GLFWwindow*)m_window->GetHandle());
	}
}

void Application::InternalShutdown(void)
{
	Shutdown();

	glfwTerminate();
}
