#pragma once
#include <Application.h>

class TetrisApp : public Application
{
public:
    TetrisApp();
    virtual ~TetrisApp();

public:
    virtual void Initialize(void);
    virtual void Update(float deltaTime);
    virtual void Shutdown(void);

private:

    // Inherited via Application
    bool ShouldClose(void) override;

    bool m_showImguiDemoWindow;
};
CREATE_APPLICATION(TetrisApp);