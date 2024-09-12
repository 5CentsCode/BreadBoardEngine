#pragma once
#include <Typedefs.h>
#include <Components/Transform.h>
#include <Components/Camera.h>

class EditorCamera
{
public:

	EditorCamera();
	~EditorCamera();

public:

	void Update(float deltaTime);

	Component::Transform& GetTransform();
	Component::Camera& GetCamera();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

private:

	Component::Transform m_transform;
	Component::Camera m_camera;

	float m_movementSpeed;
	float m_rotationSpeed;
};