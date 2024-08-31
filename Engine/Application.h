#pragma once
#include "Typedefs.h"
#include <entt/entt.hpp>
#include "ResourceManager.h" // TEMP
#include "Window.h"

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

	float m_minFrameTime = std::numeric_limits<float>::max();
	float m_maxFrameTime = std::numeric_limits<float>::min();
	std::array<float, 1000> m_frameTimeGraph;

private:

	float m_previousTime;
};

std::unique_ptr<Application> CreateApplication();
#define CREATE_APPLICATION(T)						\
std::unique_ptr<Application> CreateApplication()	\
{													\
	return std::make_unique<T>();					\
}