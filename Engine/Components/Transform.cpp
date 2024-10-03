#include "Components/Transform.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

using namespace Component;

Transform::Transform()
{
	m_dirty = true;
	m_position = glm::vec3(0.0f);
	m_rotation = glm::identity<glm::quat>();
	m_scale = glm::vec3(1.0f);
	m_worldMatrix = glm::identity<glm::mat4>();
}

glm::vec3 Transform::GetPosition() const
{
	return m_position;
}

glm::quat Transform::GetRotation() const
{
	return m_rotation;
}

glm::vec3 Transform::GetEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(m_rotation));
}

glm::vec3 Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetPosition(glm::vec3 position)
{
	m_position = position;
	m_dirty = true;
}

void Transform::SetRotation(glm::quat rotation)
{
	m_rotation = rotation;
	m_dirty = true;
}

void Transform::SetEulerAngles(glm::vec3 eulerAngles)
{
	m_rotation = glm::quat(glm::radians(eulerAngles));
	m_dirty = true;
}

void Transform::SetScale(glm::vec3 scale)
{
	m_scale = scale;
	m_dirty = true;
}

void Component::Transform::Rotate(glm::vec3 eulerAngles)
{
	m_rotation *= glm::quat(eulerAngles);
	m_dirty = true;
}

glm::vec3 Transform::GetForward() const
{
	glm::vec3 forward = glm::normalize(m_rotation * VEC3_FORWARD);
	return forward;
}

glm::vec3 Transform::GetUp() const
{
	glm::vec3 up = glm::normalize(m_rotation * VEC3_UP);
	return up;
}

glm::vec3 Transform::GetRight() const
{
	glm::vec3 right = glm::normalize(m_rotation * VEC3_RIGHT);
	return right;
}

void Transform::SetForward(glm::vec3 forward)
{
	glm::vec3 forwardNormal = glm::normalize(forward);
	SetDirection(VEC3_FORWARD, forwardNormal);
}

void Transform::SetUp(glm::vec3 up)
{
	glm::vec3 upNormal = glm::normalize(up);
	SetDirection(VEC3_UP, upNormal);
}

void Transform::SetRight(glm::vec3 right)
{
	glm::vec3 rightNormal = glm::normalize(right);
	SetDirection(VEC3_RIGHT, rightNormal);
}

void Transform::SetDirection(glm::vec3 globalDirection, glm::vec3& localDirection)
{
	glm::vec3 axis = glm::normalize(glm::cross(globalDirection, localDirection));
	if (axis.length() > 1.0f)
	{
		axis = localDirection;
	}
	float angle = glm::acos(glm::dot(globalDirection, localDirection));
	glm::quat rotationDirection = glm::angleAxis(angle, axis);
	SetRotation(rotationDirection);
}

glm::mat4 Transform::GetWorldMatrix()
{
	if (m_dirty)
	{
		CalculateMatrices();
	}

	return m_worldMatrix;
}

void Transform::CalculateMatrices()
{
	glm::mat4 worldMatrix = glm::identity<glm::mat4>();
	worldMatrix = glm::translate(worldMatrix, m_position);
	worldMatrix *= glm::mat4_cast(m_rotation);
	worldMatrix = glm::scale(worldMatrix, m_scale);

	m_worldMatrix = worldMatrix;
	m_dirty = false;
}

void Transform::SetTransformFromMatrix(glm::mat4& matrix)
{
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(matrix, m_scale, m_rotation, m_position, skew, perspective);
	m_dirty = true;
}