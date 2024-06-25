#pragma once
#include "Typedefs.h"
#include <entt/entt.hpp>

#include "ResourceManager.h" // TEMP

class Application
{
public:

	void Initialize(void);

	void Run(void);

	void Shutdown(void);

private:

	ResourceManager m_resourceManager;

	entt::registry m_registry;
};
