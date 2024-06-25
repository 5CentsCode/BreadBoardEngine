#pragma once
#include <entt/entt.hpp>

namespace EntitySystem
{
	class BaseEntitySystem
	{
	public:
		BaseEntitySystem()
		{
		}
		virtual ~BaseEntitySystem()
		{
		}

	public:

		virtual void Update(entt::registry& registry, float deltaTime) = 0;
	};
}