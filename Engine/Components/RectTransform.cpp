#include "RectTransform.h"

Component::RectTransform::RectTransform()
	: Transform()
{
}

void Component::RectTransform::CalculateMatrices()
{
	glm::mat4 worldMatrix = glm::identity<glm::mat4>();
	worldMatrix = glm::translate(worldMatrix, m_position);
	worldMatrix *= glm::mat4_cast(m_rotation);
	worldMatrix = glm::scale(worldMatrix, m_scale);

	m_lookAtMatrix = glm::lookAt(m_position, m_position + GetForward(), GetUp());

	m_worldMatrix = worldMatrix;
	m_dirty = false;
}
