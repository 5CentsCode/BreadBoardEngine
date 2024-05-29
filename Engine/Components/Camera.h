#pragma once
#include "Typedefs.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Component
{
	struct Camera
	{
		enum class ProjectionMode : uint8
		{
			Orthographic = 0,
			Perspective = 1
		};

	public:

		Camera();
		~Camera();

		float GetNearClippingPlane() const;
		float GetFarClippingPlane() const;
		float GetFieldOfView() const;
		float GetAspectRatio() const;
		ProjectionMode GetProjectionMode() const;
		float GetOrthographicSize() const;

		void SetNearClippingPlane(float nearClippingPlane);
		void SetFarClippingPlane(float farClippingPlane);
		void SetClippingPlanes(float newClippingPlane, float farClippingPlane);

		void SetFieldOfView(float fieldOfView);
		void SetAspectRatio(float aspectRatio);
		void SetProjectionMode(ProjectionMode projectionMode);
		void SetOrthographicSize(float orthographicSize);

		glm::mat4 GetProjectionMatrix();

	private:

		void CalculateProjectionMatrix();

	private:

		float m_nearClippingPlane;
		float m_farClippingPlane;

		float m_fieldOfView;
		float m_aspectRatio;
		float m_orthographicSize;

		ProjectionMode m_projectionMode = ProjectionMode::Perspective;

		glm::mat4 m_projectionMatrix = glm::identity<glm::mat4>();

		bool m_dirty;
	};
}