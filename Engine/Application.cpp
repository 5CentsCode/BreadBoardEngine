#include "Application.h"
#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>

Application::Application()
{
	m_currentFrameTime = 0.0f;
	m_previousFrameTime = 0.0f;
	m_deltaTime = 0.0f;
	m_currentFrame = 0;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Required ImGui Docking Branch
}

Application::~Application()
{
	ResourceManager::Clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Application::RenderTriangles(int32 indexCount)
{
	glDrawArrays(GL_TRIANGLES, 0, indexCount);
}

void Application::InternalInitialize(void)
{
	m_window = std::make_unique<Window>(800, 600, "Hello Window");

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_window->GetHandle(), true);
	ImGui_ImplOpenGL3_Init();

	Initialize();
}

void Application::InternalRun(void)
{
	// Set initial frame time information to capture the first frame of the application
	m_previousFrameTime = m_currentFrameTime;
	m_currentFrameTime = (float)glfwGetTime();
	m_deltaTime = m_currentFrameTime - m_previousFrameTime;

	while (m_window->ShouldClose() == false)
	{
		// Increment the frame number at the beginning of the frame
		m_currentFrame++;

		Input::PollInputEvents();

		bool escapePressed = Input::IsKeyPressed(KeyCode::Escape);
		if (escapePressed)
		{
			m_window->Close();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Update(m_deltaTime);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers((GLFWwindow*)m_window->GetHandle());

		// Update frame time information
		m_previousFrameTime = m_currentFrameTime;
		m_currentFrameTime = (float)glfwGetTime();
		m_deltaTime = m_currentFrameTime - m_previousFrameTime;
	}
}

void Application::InternalShutdown(void)
{
	Shutdown();

	glfwTerminate();
}
