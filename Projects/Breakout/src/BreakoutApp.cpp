#include "BreakoutApp.h"
#include <Components/MeshRenderer.h>
#include <Components/RectTransform.h>
#include <Components/Sprite.h>
#include "Paddle.h"
#include "Ball.h"

BreakoutApp::BreakoutApp()
	: Application()
{
}

BreakoutApp::~BreakoutApp()
{
}

entt::entity BreakoutApp::CreateSpriteEntity(glm::vec3 position, glm::vec3 size, std::shared_ptr<Texture> texture, glm::vec3 colorTint)
{
	std::shared_ptr<Shader> spriteShader = ResourceManager::LoadShader("SpriteShader", std::string(PROJECT_ASSET_PATH) + "Sprite.vert", std::string(PROJECT_ASSET_PATH) + "Sprite.frag");
	std::shared_ptr<Mesh> quadMesh = ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "quad.obj");

	entt::entity entity = m_registry.create();
	
	Component::RectTransform& transform = m_registry.emplace<Component::RectTransform>(entity);
	transform.SetPosition(position);
	transform.SetScale(size);

	Component::Sprite& sprite = m_registry.emplace<Component::Sprite>(entity);
	sprite.Texture = texture;
	sprite.ColorTint = colorTint;

	Component::MeshRenderer& meshRenderer = m_registry.emplace<Component::MeshRenderer>(entity);
	meshRenderer.Mesh = quadMesh;

	return entity;
}

void BreakoutApp::Initialize(void)
{
	// Load Resources
	std::shared_ptr<Texture> ballTexture = ResourceManager::LoadTexture(std::string(PROJECT_ASSET_PATH) + "awesomeface.png");
	std::shared_ptr<Texture> paddleTexture = ResourceManager::LoadTexture(std::string(PROJECT_ASSET_PATH) + "paddle.png");
	
	// Create entities
	m_gameLevel = std::make_unique<GameLevel>();
	m_gameLevel->Load((std::string(PROJECT_ASSET_PATH) + "levels/level1.txt").c_str(), m_registry, m_window->GetSize());

	entt::entity paddleEntity = CreateSpriteEntity(glm::vec3(0.0f, (m_window->GetHeight() * -0.5f) + 20.0f, 1.0f), glm::vec3(100.0f, 20.0f, 1.0f), paddleTexture, glm::vec3(1.0f, 1.0f, 1.0f));
	m_registry.emplace<Component::Paddle>(paddleEntity);

	entt::entity ballEntity = CreateSpriteEntity(glm::vec3(0.0f, (m_window->GetHeight() * -0.5f) + 20.0f, 2.0f), glm::vec3(30.0f), ballTexture, glm::vec3(1.0f, 1.0f, 1.0f));
	Component::Ball& ball = m_registry.emplace<Component::Ball>(ballEntity);
	ball.Velocity = glm::vec2(0.6f, 0.1f) * 500.0f;

	// Create Systems
	m_renderSystem = std::make_unique<EnttSystem::RenderSystem>(m_window);
	m_paddleSystem = std::make_unique<EnttSystem::PaddleSystem>(m_window);
	m_ballSystem = std::make_unique<EnttSystem::BallSystem>(m_window);
}

void BreakoutApp::Update(float deltaTime)
{
	m_renderSystem->Update(m_registry, deltaTime);
	m_paddleSystem->Update(m_registry, deltaTime);
	m_ballSystem->Update(m_registry, deltaTime);
}

void BreakoutApp::Shutdown(void)
{
}
