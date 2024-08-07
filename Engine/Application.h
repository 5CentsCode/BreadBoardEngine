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

private:
	
	void InternalInitialize(void);
	void InternalRun(void);
	void InternalShutdown(void);

protected:

	std::shared_ptr<Window> m_window;

	ResourceManager m_resourceManager;

	entt::registry m_registry;

private:

	float m_previousTime;
};

std::unique_ptr<Application> CreateApplication();
#define CREATE_APPLICATION(T)						\
std::unique_ptr<Application> CreateApplication()	\
{													\
	return std::make_unique<T>();					\
}