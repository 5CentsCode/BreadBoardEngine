#include "PaddleSystem.h"
#include "Paddle.h"
#include <Input.h>
#include <Components/RectTransform.h>

using namespace EnttSystem;

PaddleSystem::PaddleSystem()
{
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

		transform.SetPosition(transform.GetPosition() + glm::vec3(direction * 500.0f * deltaTime, 0.0f, 0.0f));
	});
}
