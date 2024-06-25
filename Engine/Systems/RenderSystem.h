#pragma once
#include "BaseSystem.h"

namespace EntitySystem
{
	class RenderSystem : public BaseEntitySystem
	{
	public:
		RenderSystem();
		~RenderSystem();

		void Update(entt::registry& registry, float deltaTime) override;
	};
}