#include "GameLevel.h"
#include <fstream>
#include <sstream>
#include <string>
#include <Components/RectTransform.h>
#include <Texture.h>
#include <ResourceManager.h>
#include <Components/Sprite.h>

GameLevel::GameLevel()
{
	m_width = 0;
	m_height = 0;
}

GameLevel::~GameLevel()
{
}

void GameLevel::Load(const char* filepath,  entt::registry& registry, glm::vec2 windowSize)
{
	m_bricks.clear();
	m_width = 0;
	m_height = 0;

	int32 tileCode;

	std::string line;
	std::ifstream fstream(filepath);
	std::vector<std::vector<unsigned int>> brickData;

	if (fstream)
	{
		// read each line from level file
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;

			int rowWidth = 0;
			// read each word separated by spaces
			while (sstream >> tileCode)
			{
				row.push_back(tileCode);
				rowWidth++;
			}
			m_width = glm::max(m_width, rowWidth);

			brickData.push_back(row);
			m_height++;
		}

		glm::vec3 tintColors[] =
		{
			glm::vec3(1.0f),
			glm::vec3(0.2f, 0.6f, 1.0f),
			glm::vec3(0.0f, 0.7f, 0.0f),
			glm::vec3(0.8f, 0.8f, 0.4f),
			glm::vec3(1.0f, 0.5f, 0.0f)
		};

		if (brickData.size() > 0)
		{
			std::shared_ptr<Texture> breakableBrickTexture = ResourceManager::LoadTexture(std::string(PROJECT_ASSET_PATH) + "breakablebrick.png");
			std::shared_ptr<Texture> solidBrickTexture = ResourceManager::LoadTexture(std::string(PROJECT_ASSET_PATH) + "solidbrick.png");

			glm::vec3 offset = glm::vec3(-windowSize.x, windowSize.y, 0.0f) * 0.5f;
			glm::vec3 brickSize = glm::vec3(windowSize.x / m_width, (windowSize.y * 0.5f) / m_height, 1.0f);

			for (int y = 0; y < m_height; y++)
			{
				for (int x = 0; x < m_width; x++)
				{
					int brickType = brickData[y][x];
					if (brickType == 0)
					{
						continue;
					}

					entt::entity brickEntity = registry.create();
					Component::RectTransform& transform = registry.emplace<Component::RectTransform>(brickEntity);
					transform.SetScale(brickSize);
					transform.SetPosition(brickSize * glm::vec3(x, -(y + 1), 1.0f) + (offset + (brickSize * 0.5f)));
					Brick& brick = registry.emplace<Brick>(brickEntity);
					Component::Sprite& sprite = registry.emplace<Component::Sprite>(brickEntity);

					if (brickType == 1)
					{
						brick.BrickType = BrickType::Solid;
						sprite.Texture = solidBrickTexture;
					}
					else if (brickType > 1)
					{
						brick.BrickType = BrickType::Breakable;
						sprite.Texture = breakableBrickTexture;
						sprite.ColorTint = tintColors[brickType - 1];
					}
				}
			}
		}
	}
}