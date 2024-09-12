#include "Components/Camera.h"
#include <assert.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace Component;

Camera::Camera()
{
	m_nearClippingPlane = 0.1f;
	m_farClippingPlane = 100.0f;
	m_fieldOfView = 45.0f;
	m_aspectRatio = 1.77777f;
	m_orthographicSize = 5.0f;
	m_projectionMode = ProjectionMode::Perspective;
	m_projectionMatrix = glm::identity<glm::mat4>();
	m_dirty = true;
}

Camera::~Camera()
{
}

float Camera::GetNearClippingPlane() const
{
	return m_nearClippingPlane;
}

float Camera::GetFarClippingPlane() const
{
	return m_farClippingPlane;
}

float Camera::GetFieldOfView() const
{
	return m_fieldOfView;
}

float Camera::GetAspectRatio() const
{
	return m_aspectRatio;
}

Camera::ProjectionMode Camera::GetProjectionMode() const
{
	return m_projectionMode;
}

float Camera::GetOrthographicSize() const
{
	return m_orthographicSize;
}

void Camera::SetNearClippingPlane(float nearClippingPlane)
{
	SetClippingPlanes(nearClippingPlane, m_farClippingPlane);
	m_dirty = true;
}

void Camera::SetFarClippingPlane(float farClippingPlane)
{
	SetClippingPlanes(m_nearClippingPlane, farClippingPlane);
	m_dirty = true;
}

void Camera::SetClippingPlanes(float nearClippingPlane, float farClippingPlane)
{
	assert(nearClippingPlane > 0.0f);
	assert(farClippingPlane > 0.0f);
	assert(nearClippingPlane < farClippingPlane);

	m_nearClippingPlane = nearClippingPlane;
	m_farClippingPlane = farClippingPlane;
	m_dirty = true;
}

void Camera::SetFieldOfView(float fieldOfView)
{
	assert(fieldOfView != 0.0f);

	m_fieldOfView = fieldOfView;
	m_dirty = true;
}

void Camera::SetAspectRatio(float aspectRatio)
{
	if (!std::isnan(m_aspectRatio) &&
		!std::isinf(m_aspectRatio))
	{
		m_aspectRatio = aspectRatio;
		m_dirty = true;
	}
}

void Camera::SetProjectionMode(ProjectionMode projectionMode)
{
	m_projectionMode = projectionMode;
	m_dirty = true;
}

void Camera::SetOrthographicSize(float orthographicSize)
{
	m_orthographicSize = orthographicSize;
	m_dirty = true;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (m_dirty)
	{
		CalculateProjectionMatrix();
	}
	return m_projectionMatrix;
}

void Camera::CalculateProjectionMatrix()
{
	switch (m_projectionMode)
	{
		case ProjectionMode::Orthographic:
		{
			float halfWidth = m_aspectRatio * m_orthographicSize * 0.5f;
			float halfHeight = m_orthographicSize * 0.5f;
			m_projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, m_nearClippingPlane, m_farClippingPlane);
			break;
		}

		case ProjectionMode::Perspective:
		{
			m_projectionMatrix = glm::perspective(glm::radians(m_fieldOfView), m_aspectRatio, m_nearClippingPlane, m_farClippingPlane);
			break;
		}
	}

	m_dirty = false;
	// m_projectionMatrix = glm::scale(m_projectionMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));
}
