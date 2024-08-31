#include "PaddleSystem.h"
#include <Input.h>
#include <Components/RectTransform.h>
#include "Paddle.h"

using namespace EnttSystem;

PaddleSystem::PaddleSystem(std::shared_ptr<Window> window)
{
	m_window = window;
}

PaddleSystem::~PaddleSystem()
{
}

void PaddleSystem::Update(entt::registry& registry, float deltaTime)
{
	registry.view<Component::RectTransform, Component::Paddle>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::RectTransform& transform)
	{
		int direction = 0;
		direction -= Input::IsKeyDown(KeyCode::A) ? 1 : 0;
		direction += Input::IsKeyDown(KeyCode::D) ? 1 : 0;

		glm::vec3 position = transform.GetPosition();
		position += glm::vec3(direction * 500.0f * deltaTime, 0.0f, 0.0f);
		float distanceFromCenter = (m_window->GetWidth() - transform.GetScale().x) * 0.5f;
		position.x = glm::clamp(position.x, -distanceFromCenter, distanceFromCenter);
		transform.SetPosition(position);
	});
}
