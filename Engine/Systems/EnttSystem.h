#pragma once
#include <entt/entt.hpp>

namespace EnttSystem
{
	class EnttSystem
	{
	public:
		EnttSystem()
		{
		}
		virtual ~EnttSystem()
		{
		}

	public:

		virtual void Update(entt::registry& registry, float deltaTime) = 0;
	};
}