#pragma once
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"

class StaticRenderer
{
public:

	static void SetCamera(Component::Camera* camera, Component::Transform* cameraTransform);

	static void RenderMesh(Component::Transform& transform, const Component::MeshRenderer& meshRenderer);

	static void RenderLine(const glm::vec3& point1, const glm::vec3& point2, const glm::vec4& color);

private:

	static Component::Camera* s_camera;
	static Component::Transform* s_cameraTransform;
};