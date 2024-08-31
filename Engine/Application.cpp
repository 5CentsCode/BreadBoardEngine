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
	m_previousTime = 0.0f;

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
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (m_window->ShouldClose() == false)
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
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

		Update(deltaTime);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers((GLFWwindow*)m_window->GetHandle());
	}
}

void Application::InternalShutdown(void)
{
	Shutdown();

	glfwTerminate();
}
