#pragma once
#include "Typedefs.h"
#include <entt/entt.hpp>
#include "ResourceManager.h" // TEMP
#include "Window.h"
#include "Editor/EditorCamera.h"

class Application
{
	friend int main(void);

public:
	Application();
	virtual ~Application();

public:

	virtual void Initialize(void) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Shutdown(void) = 0;

	// TEMP
	void RenderTriangles(int32 indexCount);

private:

	void InternalInitialize(void);
	void InternalRun(void);
	void InternalShutdown(void);

protected:

	std::shared_ptr<Window> m_window;

	ResourceManager m_resourceManager;

	entt::registry m_registry;

	float m_currentFrameTime;
	float m_previousFrameTime;
	float m_deltaTime;
	uint64 m_currentFrame;

	EditorCamera m_editorCamera;
};

std::unique_ptr<Application> CreateApplication();
#define CREATE_APPLICATION(T)						\
std::unique_ptr<Application> CreateApplication()	\
{													\
	return std::make_unique<T>();					\
}