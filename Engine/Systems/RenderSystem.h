#pragma once
#include "EnttSystem.h"
#include "Mesh.h"
#include "Window.h"

namespace EnttSystem
{
	class RenderSystem : public EnttSystem
	{
	public:
		RenderSystem(Window* window, Mesh* quadMesh);
		~RenderSystem();

		void Update(entt::registry& registry, float deltaTime) override;

	private:

		Window* m_window;
		Mesh* m_quadMesh;
	};
}