#pragma once
#include <Application.h>

class BreakoutApp : public Application
{
public:
	BreakoutApp();
	virtual ~BreakoutApp();

public:
	virtual void Initialize(void);
	virtual void Update(float deltaTime);
	virtual void Shutdown(void);
};
CREATE_APPLICATION(BreakoutApp);