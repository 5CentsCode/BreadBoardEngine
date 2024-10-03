#pragma once
#include <Application.h>

class BulletMMOApp : public Application
{
public:
	BulletMMOApp();
	virtual ~BulletMMOApp();

public:
	virtual void Initialize(void);
	virtual void Update(float deltaTime);
	virtual void Shutdown(void);
	virtual bool ShouldClose(void);

private:
};
CREATE_APPLICATION(BulletMMOApp);