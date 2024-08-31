#include "BallSystem.h"
#include <Components/RectTransform.h>
#include "Ball.h"

using namespace EnttSystem;

BallSystem::BallSystem(std::shared_ptr<Window> window)
{
	m_window = window;
}

BallSystem::~BallSystem()
{
}

void BallSystem::Update(entt::registry& registry, float deltaTime)
{
	registry.view<Component::RectTransform, Component::Ball>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::RectTransform& transform, Component::Ball& ball)
	{
		glm::vec3 position = transform.GetPosition();
		position += glm::vec3(ball.Velocity, 0.0f) * deltaTime;

		glm::vec2 halfDistanceFromCenter = (glm::vec2(m_window->GetSize()) - glm::vec2(transform.GetScale())) * 0.5f;

		if (position.x <= -halfDistanceFromCenter.x ||
			position.x >= halfDistanceFromCenter.x)
		{
			ball.Velocity.x *= -1.0f;
		}
		if (position.y <= -halfDistanceFromCenter.y ||
			position.y >= halfDistanceFromCenter.y)
		{
			ball.Velocity.y *= -1.0f;
		}

		position.x = glm::clamp(position.x, -halfDistanceFromCenter.x, halfDistanceFromCenter.x);
		position.y = glm::clamp(position.y, -halfDistanceFromCenter.y, halfDistanceFromCenter.y);

		transform.SetPosition(position);
	});
}