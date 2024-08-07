#pragma once
#include <Typedefs.h>
#include <entt/entt.hpp>
#include <memory>
#include <vector>
#include "Brick.h"

struct GameLevel
{
public:
	GameLevel();
	~GameLevel();

public:

	void Load(const char* filepath, entt::registry& registry, glm::vec2 windowSize);

private:
	int32 m_width;
	int32 m_height;

	std::vector<std::shared_ptr<Brick>> m_bricks;
};