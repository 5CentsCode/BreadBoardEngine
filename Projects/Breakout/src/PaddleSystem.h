#pragma once
#include <Typedefs.h>
#include <Systems/EnttSystem.h>

namespace EnttSystem
{
	class PaddleSystem : public EnttSystem
	{
	public:
		PaddleSystem();
		~PaddleSystem();

		void Update(entt::registry& registry, float deltaTime) override;
	};
}