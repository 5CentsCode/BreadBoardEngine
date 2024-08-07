#pragma once
#include <Typedefs.h>
#include <Systems/EnttSystem.h>
#include <Window.h>

namespace EnttSystem
{
	class PaddleSystem : public EnttSystem
	{
	public:
		PaddleSystem(std::shared_ptr<Window> window);
		~PaddleSystem();

		void Update(entt::registry& registry, float deltaTime) override;

	private:
		std::shared_ptr<Window> m_window;
	};
}