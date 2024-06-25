#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

#include "Components/Camera.h" // TEMP
#include "Components/Light.h" // TEMP
#include "Components/MeshRenderer.h" // TEMP
#include "Components/Transform.h" // TEMP
#include "Input.h" // TEMP?
#include "Material.h" // TEMP
#include "Mesh.h" // TEMP
#include "Shader.h" // TEMP
#include "Texture.h" // TEMP
#include "Systems/RenderSystem.h"

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
	std::shared_ptr<Shader> modelShader = m_resourceManager.LoadShader("MaterialShader", std::string(PROJECT_ASSET_PATH) + "Shaders/Material.vert", std::string(PROJECT_ASSET_PATH) + "Shaders/Material.frag");
	std::shared_ptr<Shader> lightShader = m_resourceManager.LoadShader("lightShader", std::string(PROJECT_ASSET_PATH) + "Shaders/LightEdit.vert", std::string(PROJECT_ASSET_PATH) + "Shaders/LightEdit.frag");
	std::shared_ptr<Mesh> cubeMesh = m_resourceManager.LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/cube.obj");
	std::shared_ptr<Mesh> icosphereMesh = m_resourceManager.LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/icosphere.obj");
	std::shared_ptr<Texture> texture = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/TestTexture.png");
	
	std::shared_ptr<Texture> cobblestoneAlbedo = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_albedo.png");
	std::shared_ptr<Texture> cobblestoneNormal = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_normals.png");
	std::shared_ptr<Texture> cobblestoneRoughness = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_roughness.png");
	std::shared_ptr<Texture> cobblestoneMetal = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/cobblestone_pbr/cobblestone_metal.png");

	std::shared_ptr<Texture> containerAlbedo = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/container/albedo.png");
	std::shared_ptr<Texture> containerRoughness = m_resourceManager.LoadTexture(std::string(PROJECT_ASSET_PATH) + "Textures/container/roughness.png");

	std::shared_ptr<Texture> albedoTexture = m_resourceManager.CreateColorTexture(glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));

	Material cobblestoneMat = Material(0, std::string("Cobblestone_pbr"));
	cobblestoneMat.SetShader(modelShader);
	cobblestoneMat.SetAlbedoTexture(albedoTexture);
	cobblestoneMat.SetNormalTexture(cobblestoneNormal);
	cobblestoneMat.SetRoughnessTexture(containerRoughness);
	cobblestoneMat.SetMetalTexture(cobblestoneMetal);

	for (unsigned int i = 0; i < 10; i++)
	{
		entt::entity cubeEntity = m_registry.create();
		Component::Transform& cubeTransform = m_registry.emplace<Component::Transform>(cubeEntity);
		cubeTransform.SetPosition(cubePositions[i]);
		Component::MeshRenderer& cubeRenderer = m_registry.emplace<Component::MeshRenderer>(cubeEntity);
		cubeRenderer.Material = std::make_shared<Material>(cobblestoneMat);
		cubeRenderer.Mesh = cubeMesh;
	}

	EntitySystem::RenderSystem renderSystem;

	Component::Transform lightTransform;
	lightTransform.SetScale(glm::vec3(0.2f));
	lightTransform.SetPosition(glm::vec3(1.2f, 1.0f, 2.0f));
	lightTransform.SetForward(-lightTransform.GetPosition());
	Component::Light light;
	light.Color = glm::vec3(1.0f);
	light.Intensity = 5.0f;

	entt::entity cameraEntity = m_registry.create();
	Component::Transform& cameraTransform = m_registry.emplace<Component::Transform>(cameraEntity);
	cameraTransform.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Component::Camera& cameraComponent = m_registry.emplace<Component::Camera>(cameraEntity);
	cameraComponent.SetAspectRatio((float)window.GetWidth() / (float)window.GetHeight());

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
		if (Input::IsKeyDown(KeyCode::X))
		{
			cameraMovement += cameraTransform.GetUp() * cameraSpeed;
		}
		if (Input::IsKeyDown(KeyCode::Z))
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

		glm::mat4 projection = cameraComponent.GetProjectionMatrix();
		glm::mat4 view = cameraTransform.GetLookAtMatrix();

		lightShader->Bind();
		icosphereMesh->Bind();
		lightShader->SetUniform("Projection", projection);
		lightShader->SetUniform("View", view);
		lightShader->SetUniform("Model", lightTransform.GetWorldMatrix());
		glDrawArrays(GL_TRIANGLES, 0, (int)icosphereMesh->GetIndexCount());
		
		cobblestoneMat.Bind();
		cubeMesh->Bind();
		modelShader->SetUniform("Projection", projection);
		modelShader->SetUniform("View", view);
		light.AddToShader(lightTransform, *modelShader);

		int i = 0;
		m_registry.view<Component::Transform, Component::MeshRenderer>()
			.each([&](const entt::entity UNUSED_PARAM(entity), Component::Transform& transform, Component::MeshRenderer& UNUSED_PARAM(meshRenderer))
		{
			float angle = 0.1f * i;

			transform.SetRotation(transform.GetRotation() * glm::angleAxis(glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)));

			i++;
		});

		renderSystem.Update(m_registry, 0.0f);

		glfwSwapBuffers((GLFWwindow*)window.GetHandle());
		Input::PollInputEvents();
	}

	modelShader->Unbind();
}

void Application::Shutdown(void)
{
	m_resourceManager.Clear();

	glfwTerminate();
}
