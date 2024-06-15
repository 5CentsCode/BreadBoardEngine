#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

#include "Material.h" // TEMP
#include "Mesh.h" // TEMP
#include "Shader.h" // TEMP
#include "Texture.h" // TEMP
#include "Components/Camera.h" // TEMP
#include "Components/Transform.h" // TEMP
#include "Input.h"

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

void Application::Initialize(void)
{
}

void Application::Run(void)
{
	Window window = Window(800, 600, "Hello Window");

	// Resources need to be loaded after a window is created
	std::shared_ptr<Shader> whiteShader = m_resourceManager.LoadShader("MaterialShader", std::string(PROJECT_ASSET_PATH) + "Shaders/Material.vert", std::string(PROJECT_ASSET_PATH) + "Shaders/Material.frag");
	std::shared_ptr<Mesh> mesh = m_resourceManager.LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/cube.obj");
	std::shared_ptr<Texture> texture = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/TestTexture.png");
	
	std::shared_ptr<Texture> cobblestoneAlbedo = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_albedo.png");
	std::shared_ptr<Texture> cobblestoneNormal = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_normals.png");
	std::shared_ptr<Texture> cobblestoneRoughness = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_roughness.png");
	std::shared_ptr<Texture> cobblestoneMetal = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_metal.png");

	Material cobblestoneMat = Material(0, std::string("Cobblestone_pbr"));
	cobblestoneMat.SetShader(whiteShader);
	cobblestoneMat.SetAlbedoTexture(cobblestoneAlbedo);
	cobblestoneMat.SetNormalTexture(cobblestoneNormal);
	cobblestoneMat.SetRoughnessTexture(cobblestoneRoughness);
	cobblestoneMat.SetMetalTexture(cobblestoneMetal);

	cobblestoneMat.Bind();

	Component::Camera camera;
	camera.SetAspectRatio((float)window.GetWidth() / (float)window.GetHeight());

	Component::Transform cameraTransform;
	cameraTransform.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));

	while (window.ShouldClose() == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		float cameraSpeed = static_cast<float>(2.5 * 0.01f);
		glm::vec3 cameraMovement = glm::vec3(0.0f);
		if (Input::IsKeyDown(KeyCode::W))
		{
			cameraMovement += cameraTransform.GetForward() * cameraSpeed;
		}
		if (Input::IsKeyDown(KeyCode::S))
		{
			cameraMovement -= cameraTransform.GetForward() * cameraSpeed;
		}
		if (Input::IsKeyDown(KeyCode::D))
		{
			cameraMovement += cameraTransform.GetRight() * cameraSpeed;
		}
		if (Input::IsKeyDown(KeyCode::A))
		{
			cameraMovement -= cameraTransform.GetRight() * cameraSpeed;
		}
		if (Input::IsKeyDown(KeyCode::Z))
		{
			cameraMovement += cameraTransform.GetUp() * cameraSpeed;
		}
		if (Input::IsKeyDown(KeyCode::X))
		{
			cameraMovement -= cameraTransform.GetUp() * cameraSpeed;
		}
		cameraTransform.SetPosition(cameraTransform.GetPosition() + cameraMovement);

		glm::vec2 mouseDelta = Input::GetMouseDelta();
		if (Input::IsMouseButtonDown(MouseCode::Right))
		{
			const float rotationSpeed = 0.2f;

			glm::quat yaw = glm::angleAxis((float)glm::radians(-mouseDelta.x * rotationSpeed), VEC3_UP);
			glm::quat pitch = glm::angleAxis((float)glm::radians(-mouseDelta.y * rotationSpeed), cameraTransform.GetRight());
			glm::quat orientation = glm::normalize(yaw * pitch);

			cameraTransform.SetRotation(glm::normalize(orientation * cameraTransform.GetRotation()));
		}

		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = glm::lookAt(cameraTransform.GetPosition(), cameraTransform.GetPosition() + cameraTransform.GetForward(), cameraTransform.GetUp());

		whiteShader->SetUniform("Projection", projection);
		whiteShader->SetUniform("View", view);

		mesh->Bind();
		for (unsigned int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			whiteShader->SetUniform("Model", model);

			glDrawArrays(GL_TRIANGLES, 0, (int)mesh->GetIndexCount());
		}

		glfwSwapBuffers((GLFWwindow*)window.GetHandle());
		Input::PollInputEvents();
	}

	whiteShader->Unbind();
}

void Application::Shutdown(void)
{
	m_resourceManager.Clear();

	glfwTerminate();
}
