#pragma once
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"

class StaticRenderer
{
public:

	static void SetCamera(std::shared_ptr<Component::Camera> camera, std::shared_ptr<Component::Transform> cameraTransform);

	static void RenderMesh(Component::Transform& transform, const Component::MeshRenderer& meshRenderer);

	static void RenderLine(const glm::vec3& point1, const glm::vec3& point2, const glm::vec4& color);

private:

	static std::shared_ptr<Component::Camera> s_camera;
	static std::shared_ptr<Component::Transform> s_cameraTransform;
};