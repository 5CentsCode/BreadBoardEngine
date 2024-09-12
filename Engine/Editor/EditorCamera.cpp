#include "EditorCamera.h"
#include <Input.h>

EditorCamera::EditorCamera()
{
	m_movementSpeed = 5.0f;
	m_rotationSpeed = 0.2f;
}

EditorCamera::~EditorCamera()
{
}

void EditorCamera::Update(float deltaTime)
{
	if (Input::IsMouseButtonDown(MouseCode::Right))
	{
		glm::vec2 mouseDelta = Input::GetMouseDelta() * -1.0f;
		glm::quat yaw = glm::angleAxis((float)glm::radians(mouseDelta.x * m_rotationSpeed), VEC3_UP);
		glm::quat pitch = glm::angleAxis((float)glm::radians(mouseDelta.y * m_rotationSpeed), m_transform.GetRight());
		glm::quat orientation = glm::normalize(yaw * pitch);

		m_transform.SetRotation(glm::normalize(orientation * m_transform.GetRotation()));
	}

	glm::vec3 cameraMovement = glm::vec3(0.0f);

	// Right / Left
	if (Input::IsKeyDown(KeyCode::D))
	{
		cameraMovement += m_transform.GetRight();
	}
	if (Input::IsKeyDown(KeyCode::A))
	{
		cameraMovement -= m_transform.GetRight();
	}

	// Up / Down
	if (Input::IsKeyDown(KeyCode::X))
	{
		cameraMovement.y += 1;
	}
	if (Input::IsKeyDown(KeyCode::Z))
	{
		cameraMovement.y -= 1;
	}

	// Forward / Backward
	if (Input::IsKeyDown(KeyCode::W))
	{
		cameraMovement += m_transform.GetForward();
	}
	if (Input::IsKeyDown(KeyCode::S))
	{
		cameraMovement -= m_transform.GetForward();
	}

	glm::vec3 position = m_transform.GetPosition();
	m_transform.SetPosition(position + ((cameraMovement * m_movementSpeed) * deltaTime));
}

Component::Transform& EditorCamera::GetTransform()
{
	return m_transform;
}

Component::Camera& EditorCamera::GetCamera()
{
	return m_camera;
}

glm::mat4 EditorCamera::GetViewMatrix()
{
	glm::vec3 position = m_transform.GetPosition();
	glm::vec3 forward = m_transform.GetForward();
	glm::vec3 up = m_transform.GetUp();

	glm::mat4 view = glm::lookAt(position, position + forward, up);
	return view;
}

glm::mat4 EditorCamera::GetProjectionMatrix()
{
	glm::mat4 projection = m_camera.GetProjectionMatrix();
	return projection;
}
