#pragma once
#include <Application.h>
#include <Systems/RenderSystem.h>
#include "GameLevel.h"
#include "PaddleSystem.h"

class BreakoutApp : public Application
{
public:
	BreakoutApp();
	virtual ~BreakoutApp();

private:

	entt::entity CreateSpriteEntity(glm::vec3 position, glm::vec3 size, std::shared_ptr<Texture> texture, glm::vec3 colorTint);

public:
	virtual void Initialize(void);
	virtual void Update(float deltaTime);
	virtual void Shutdown(void);

private:

	std::unique_ptr<EnttSystem::RenderSystem> m_renderSystem;
	std::unique_ptr<EnttSystem::PaddleSystem> m_paddleSystem;

	std::unique_ptr<GameLevel> m_gameLevel;
};
CREATE_APPLICATION(BreakoutApp);