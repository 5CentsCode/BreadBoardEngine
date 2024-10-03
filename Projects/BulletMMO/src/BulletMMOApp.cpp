#include <Components/Camera.h>
#include <Components/MeshRenderer.h>
#include <Components/Transform.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <Input.h>
#include <Shader.h>
#include <Typedefs.h>
#include "BulletMMOApp.h"

BulletMMOApp::BulletMMOApp() : Application()
{
}

BulletMMOApp::~BulletMMOApp()
{
}

void BulletMMOApp::Initialize(void)
{
	InitWindow(800, 600, "BulletMMO");
}

void BulletMMOApp::Update(float deltaTime)
{
	REFERENCE(deltaTime);
}

void BulletMMOApp::Shutdown(void)
{
}

bool BulletMMOApp::ShouldClose(void)
{
	bool shouldClose = m_window->ShouldClose();
	return shouldClose;
}