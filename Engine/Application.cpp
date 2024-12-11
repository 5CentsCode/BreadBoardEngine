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
    m_totalTime = 0.0f;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Required ImGui Docking Branch
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::Initialize(void)
{
}

void Application::Run(void)
{
    // Set initial frame time information to capture the first frame of the application
    m_previousFrameTime = m_currentFrameTime;
    m_currentFrameTime = (float)glfwGetTime();
    m_deltaTime = m_currentFrameTime - m_previousFrameTime;

    while (ShouldClose() == false)
    {
        // Increment the frame number at the beginning of the frame
        m_currentFrame++;

        Input::PollInputEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        Update(m_deltaTime);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers((GLFWwindow*)m_window->GetHandle());

        // Update frame time information
        m_previousFrameTime = m_currentFrameTime;
        m_currentFrameTime = (float)glfwGetTime();
        m_deltaTime = m_currentFrameTime - m_previousFrameTime;
        m_totalTime += m_deltaTime;
    }
}

void Application::Shutdown(void)
{
    glfwTerminate();
}

void Application::InitWindow(int width, int height, const char* title)
{
    m_window = std::make_unique<Window>(width, height, title);
    m_window->SetPosition(glm::ivec2((2560 - width) / 2, (1440 - height) / 2));

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_window->GetHandle(), true);
    ImGui_ImplOpenGL3_Init();
}