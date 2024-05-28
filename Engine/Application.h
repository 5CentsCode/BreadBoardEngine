#pragma once
#include "Typedefs.h"

#include "ResourceManager.h" // TEMP

class Application
{
public:

	void Initialize(void);

	void Run(void);

	void Shutdown(void);

private:

	ResourceManager m_resourceManager;
};
