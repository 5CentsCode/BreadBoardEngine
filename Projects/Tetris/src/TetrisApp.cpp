#include "TetrisApp.h"
#include <imgui.h>

TetrisApp::TetrisApp()
    : Application()
{
    m_showImguiDemoWindow = false;
}

TetrisApp::~TetrisApp()
{
}

void TetrisApp::Initialize(void)
{
    InitWindow(800, 600, "Hello Window");
}

void TetrisApp::Update(float deltaTime)
{
    REFERENCE(deltaTime);

    if (m_showImguiDemoWindow)
    {
        ImGui::ShowDemoWindow(&m_showImguiDemoWindow);
    }

    ImGui::Begin("Inspector");
    {
        ImGui::PushItemWidth(-160);

        if (ImGui::TreeNode("App Details"))
        {
            ImGui::Spacing();
            ImGui::Text("Frame rate: %f fps", ImGui::GetIO().Framerate);
            ImGui::Text("Window Client Size: %dx%d", m_window->GetWidth(), m_window->GetHeight());

            if (ImGui::Button(m_showImguiDemoWindow ? "Hide ImGui Demo Window" : "Show ImGui Demo Window"))
            {
                m_showImguiDemoWindow = !m_showImguiDemoWindow;
            }

            ImGui::Spacing();
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

void TetrisApp::Shutdown(void)
{
}

bool TetrisApp::ShouldClose(void)
{
    return m_window->ShouldClose();
}
