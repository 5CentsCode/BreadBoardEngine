#pragma once
#include "EnttSystem.h"
#include "Mesh.h"
#include "Window.h"

namespace EnttSystem
{
	class RenderSystem : public EnttSystem
	{
	public:
		RenderSystem(std::shared_ptr<Window> window);
		~RenderSystem();

		void Update(entt::registry& registry, float deltaTime) override;

	private:

		std::shared_ptr<Window> m_window;
	};
}