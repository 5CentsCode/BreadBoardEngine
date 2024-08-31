#include "StaticRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ResourceManager.h>
#include "Mesh.h"
#include "Shader.h"

std::shared_ptr<Component::Camera> StaticRenderer::s_camera;
std::shared_ptr<Component::Transform> StaticRenderer::s_cameraTransform;

void StaticRenderer::SetCamera(std::shared_ptr<Component::Camera> camera, std::shared_ptr<Component::Transform> cameraTransform)
{
	s_camera = camera;
	s_cameraTransform = cameraTransform;
}

void StaticRenderer::RenderMesh(Component::Transform& transform, const Component::MeshRenderer& meshRenderer)
{
	std::shared_ptr<Shader> shader = meshRenderer.Material->Shader;
	shader->Bind();

	meshRenderer.Mesh->Bind();
	shader->SetUniform("View", glm::lookAt(s_cameraTransform->GetPosition(), s_cameraTransform->GetPosition() + s_cameraTransform->GetForward(), s_cameraTransform->GetUp()));
	shader->SetUniform("Projection", s_camera->GetProjectionMatrix());
	shader->SetUniform("Model", transform.GetWorldMatrix());

	glDrawArrays(GL_TRIANGLES, 0, meshRenderer.Mesh->GetIndexCount());
}

void StaticRenderer::RenderLine(const glm::vec3& point1, const glm::vec3& point2, const glm::vec4& color)
{
	std::shared_ptr<Shader> shader = ResourceManager::LoadShader("ColorShader", std::string(PROJECT_ASSET_PATH) + "Shaders/Color.vert", std::string(PROJECT_ASSET_PATH) + "Shaders/Color.frag");;

	std::vector<Vertex> vertices
	{
		Vertex { point1, glm::vec3(0.0f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
		Vertex { point2, glm::vec3(0.0f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
	};
	std::vector<uint32> indices
	{
		0,
		1
	};
	Guid guid;
	std::string name = "Line";
	Mesh mesh = Mesh(guid, name, vertices, indices);
	mesh.Upload(false);

	mesh.Bind();
	shader->Bind();
	shader->SetUniform("View", glm::lookAt(s_cameraTransform->GetPosition(), s_cameraTransform->GetPosition() + s_cameraTransform->GetForward(), s_cameraTransform->GetUp()));
	shader->SetUniform("Projection", s_camera->GetProjectionMatrix());

	glDrawArrays(GL_LINES, 0, 2);
}
