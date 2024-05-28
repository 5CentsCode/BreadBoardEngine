#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

#include "Shader.h"

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {  // note that we start from 0!
	   0, 1, 3,  // first Triangle
	   1, 2, 3   // second Triangle
};

void Application::Initialize(void)
{
}

void Application::Run(void)
{
	Window window = Window(800, 600, "Hello Window");

	// Resources need to be loaded after a window is created
	std::shared_ptr<Shader> whiteShader = m_resourceManager.LoadShader("WhiteShader", std::string(PROJECT_ASSET_PATH) + "Shaders/White.vert", std::string(PROJECT_ASSET_PATH) + "Shaders/White.frag");
	whiteShader->Bind();

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (window.ShouldClose() == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers((GLFWwindow*)window.GetHandle());
		glfwPollEvents();
	}

	whiteShader->Unbind();
}

void Application::Shutdown(void)
{
	m_resourceManager.Clear();

	glfwTerminate();
}
