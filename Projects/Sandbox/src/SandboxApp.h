#pragma once
#include <Application.h>

class SandboxApp : public Application
{
public:
	SandboxApp();
	virtual ~SandboxApp();

public:
	virtual void Initialize(void);
	virtual void Update(float deltaTime);
	virtual void Shutdown(void);

private:

};
CREATE_APPLICATION(SandboxApp);