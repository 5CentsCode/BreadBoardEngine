#pragma once
#include "Typedefs.h"
#include <glm/gtx/quaternion.hpp>
#include <vector>

namespace Component
{
	struct Transform
	{
		Transform();

		// TODO: Add Getter/Setter Local position/rotation/euler angles/scale
		// TODO: Add Getter Local Matrix

		glm::vec3 GetPosition() const;
		glm::quat GetRotation() const;
		glm::vec3 GetEulerAngles() const;
		glm::vec3 GetScale() const;

		void SetPosition(glm::vec3 position);
		void SetRotation(glm::quat rotation);
		void SetEulerAngles(glm::vec3 eulerAngles);
		void SetScale(glm::vec3 scale);

		glm::vec3 GetForward() const;
		glm::vec3 GetUp() const;
		glm::vec3 GetRight() const;

		void SetForward(glm::vec3 forward);
		void SetUp(glm::vec3 up);
		void SetRight(glm::vec3 right);

		glm::mat4 GetWorldMatrix();

	private:

		void CalculateWorldMatrix();
		void SetTransformFromMatrix(glm::mat4& matrix);

		void SetDirection(glm::vec3 globalDirection, glm::vec3& localDirection);

	private:

		glm::vec3 m_position;
		glm::quat m_rotation;
		glm::vec3 m_scale;

		glm::mat4 m_worldMatrix;

		bool m_dirty;
	};
}