#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

#include "Shader.h" // TEMP
#include "Components/Camera.h" // TEMP
#include "Components/Transform.h" // TEMP

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {  // note that we start from 0!
	   0, 1, 3,  // first Triangle
	   1, 2, 3   // second Triangle
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, 15.0f),
	glm::vec3(-1.5f, -2.2f, 2.5f),
	glm::vec3(-3.8f, -2.0f, 12.3f),
	glm::vec3(2.4f, -0.4f, 3.5f),
	glm::vec3(-1.7f,  3.0f, 7.5f),
	glm::vec3(1.3f, -2.0f, 2.5f),
	glm::vec3(1.5f,  2.0f, 2.5f),
	glm::vec3(1.5f,  0.2f, 1.5f),
	glm::vec3(-1.3f,  1.0f, 1.5f)
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

	Component::Camera camera;
	camera.SetAspectRatio((float)window.GetWidth() / (float)window.GetHeight());

	Component::Transform cameraTransform;
	cameraTransform.SetPosition(glm::vec3(0.0f, 0.0f, -3.0f));
	cameraTransform.SetForward(glm::vec3(0.0f, 0.0f, 1.0f));

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (window.ShouldClose() == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		float cameraSpeed = static_cast<float>(2.5 * 0.01f);
		if (glfwGetKey((GLFWwindow*)window.GetHandle(), GLFW_KEY_W) == GLFW_PRESS)
			cameraTransform.SetPosition(cameraTransform.GetPosition() + cameraTransform.GetForward() * cameraSpeed);
		if (glfwGetKey((GLFWwindow*)window.GetHandle(), GLFW_KEY_S) == GLFW_PRESS)
			cameraTransform.SetPosition(cameraTransform.GetPosition() - cameraTransform.GetForward() * cameraSpeed);
		if (glfwGetKey((GLFWwindow*)window.GetHandle(), GLFW_KEY_A) == GLFW_PRESS)
			cameraTransform.SetPosition(cameraTransform.GetPosition() - cameraTransform.GetRight() * cameraSpeed);
		if (glfwGetKey((GLFWwindow*)window.GetHandle(), GLFW_KEY_D) == GLFW_PRESS)
			cameraTransform.SetPosition(cameraTransform.GetPosition() + cameraTransform.GetRight() * cameraSpeed);

		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = glm::lookAt(cameraTransform.GetPosition(), cameraTransform.GetPosition() + cameraTransform.GetForward(), cameraTransform.GetUp());

		whiteShader->SetUniform("Projection", projection);
		whiteShader->SetUniform("View", view);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			whiteShader->SetUniform("Model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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
