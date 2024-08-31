#pragma once
#include <Typedefs.h>
#include <Systems/EnttSystem.h>
#include <Window.h>

namespace EnttSystem
{
	class BallSystem : public EnttSystem
	{
	public:
		BallSystem(std::shared_ptr<Window> window);
		~BallSystem();

		void Update(entt::registry& registry, float deltaTime) override;

	private:
		std::shared_ptr<Window> m_window;
	};
}