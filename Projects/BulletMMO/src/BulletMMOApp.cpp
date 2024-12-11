#include "BulletMMOApp.h"
#include <filesystem>
#include <imgui.h>
#include <Components/Camera.h> // TEMP
#include <Components/Transform.h> // TEMP
#include <DataType/Model.h> // TEMP
#include <DataType/Texture.h> // TEMP
#include <Draw.h> // TEMP
#include <Shader.h> // TEMP
#include <Input.h> // TEMP

Shader shader;
Model quadModel;
Model quadModel2;
Model cubeModel;
Component::Camera cam;
Component::Transform camTransform;
glm::vec3 camDirection = glm::vec3(0.0f, -15.0f, -3.0f);
float camDistance = glm::length(camDirection);

BulletMMOApp::BulletMMOApp() : Application()
{
}

BulletMMOApp::~BulletMMOApp()
{
}

void BulletMMOApp::Initialize(void)
{
    InitWindow(800, 600, "BulletMMO");

    std::filesystem::path workingDirectory = std::filesystem::current_path();

    std::string vertexFileName = workingDirectory.string() + "/Assets/Shaders/Default.vs";
    std::string fragmentFileName = workingDirectory.string() + "/Assets/Shaders/Texture.fs";
    shader = LoadShader(vertexFileName.c_str(), fragmentFileName.c_str());

    std::string quadFileName = workingDirectory.string() + "/Assets/Models/quad.obj";
    std::string cubeFileName = workingDirectory.string() + "/Assets/Models/Cube.obj";

    quadModel = LoadModel(quadFileName.c_str());
    quadModel2 = quadModel;
    cubeModel = LoadModel(cubeFileName.c_str());
    Texture colorTexture = CreateColorTexture(Color(1.0f));
    std::string rainbowFileName = workingDirectory.string() + "/Assets/Textures/Rainbow.png";
    std::string grassFileName = workingDirectory.string() + "/Assets/Textures/Grass.png";
    Texture rainbowTexture = LoadTexture(rainbowFileName.c_str());
    Texture grassTexture = LoadTexture(grassFileName.c_str());

    Material rainbowMat;
    rainbowMat.Shader = shader;
    rainbowMat.Texture = rainbowTexture;

    Material grassMat;
    grassMat.Shader = shader;
    grassMat.Texture = grassTexture;

    quadModel.Materials.push_back(rainbowMat);
    quadModel2.Materials.push_back(grassMat);
    cubeModel.Materials.push_back(rainbowMat);

    camDirection = glm::normalize(camDirection);
    cam.SetAspectRatio(800.0f / 600.0f);
    cam.SetFieldOfView(60.0f);
    camTransform.SetPosition(glm::vec3(0.0f, 15.0f, 0.0f));
    camTransform.SetForward(camDirection);

    Draw::SetCamera(&cam, &camTransform);
}

void BulletMMOApp::Update(float deltaTime)
{
    REFERENCE(deltaTime);

    cam.SetAspectRatio(m_window->GetAspectRatio());

    if (Input::IsMouseButtonDown(MouseCode::Right))
    {
        // glm::vec2 mouseDelta = Input::GetMouseDelta() * -1.0f;
        // glm::quat yaw = glm::angleAxis((float)glm::radians(mouseDelta.x * 0.25f), VEC3_UP);
        // glm::quat pitch = glm::angleAxis((float)glm::radians(mouseDelta.y * 0.25f), camTransform.GetRight());
        // glm::quat orientation = glm::normalize(yaw * pitch);
        //
        // camTransform.SetRotation(glm::normalize(orientation * camTransform.GetRotation()));
    }

    glm::vec3 movement = glm::vec3(0.0f);
    float rotation = 0.0f;

    glm::vec3 forward = camTransform.GetForward();
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    glm::vec3 right = camTransform.GetRight();
    right.y = 0.0f;
    right = glm::normalize(right);

    if (Input::IsKeyDown(KeyCode::W))
    {
        movement += forward;
    }
    if (Input::IsKeyDown(KeyCode::S))
    {
        movement -= forward;
    }

    if (Input::IsKeyDown(KeyCode::A))
    {
        movement -= right;
    }
    if (Input::IsKeyDown(KeyCode::D))
    {
        movement += right;
    }

    if (Input::IsKeyDown(KeyCode::Q))
    {
        rotation += 1.0f;
    }
    if (Input::IsKeyDown(KeyCode::E))
    {
        rotation -= 1.0f;
    }
    movement.y = 0.0f;

    glm::vec3 camForward = camTransform.GetForward();
    glm::vec3 camPosition = camTransform.GetPosition();
    glm::vec3 camCenter = camPosition + camForward * camDistance;
    camCenter.y = 0.0f;

    if (glm::abs(rotation) > 0.0f)
    {
        glm::quat yaw = glm::angleAxis((float)glm::radians(rotation * 100.0f * deltaTime), VEC3_UP);
        glm::quat orientation = glm::normalize(yaw);

        camTransform.SetRotation(glm::normalize(orientation * camTransform.GetRotation()));
        camDirection = camTransform.GetForward();

        camPosition = camCenter - camDirection * camDistance;
        camTransform.SetPosition(camPosition);
    }

    if (glm::length(movement) > 0)
    {
        movement = glm::normalize(movement) * 5.0f * deltaTime;
        camCenter += movement;

        camPosition = camCenter - camDirection * camDistance;
        camTransform.SetPosition(camPosition);
    }

    glm::vec3 tileOffset = glm::floor(camCenter);
    tileOffset.y = 0.0f;

    int planeSize = 20;
    for (int32 y = -planeSize; y < planeSize; y++)
    {
        for (int32 x = -planeSize; x < planeSize; x++)
        {
            Draw::DrawModel(quadModel2, tileOffset + glm::vec3(x, 0.0f, y), glm::identity<glm::quat>(), glm::vec3(0.5f), Color(1.0f));
        }
    }

    glm::vec3 playerPosition = camCenter;
    playerPosition.y = 0.25f;
    Draw::DrawBillboard(quadModel, glm::vec3(playerPosition), 0.0f, glm::vec3(0.5f), Color(1.0f));
    Draw::DrawBillboard(quadModel, glm::vec3(3.0, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f), Color(1.0f));
    // Draw::DrawModel(cubeModel, glm::vec3(3.0, 2.0f, 0.0f), glm::identity<glm::quat>(), glm::vec3(0.5f), Color(1.0f));
    Draw::DrawModel(cubeModel, glm::vec3(3.0, 0.5f, 3.0f), glm::identity<glm::quat>(), glm::vec3(1.0f), Color(1.0f));
}

void BulletMMOApp::Shutdown(void)
{
}

bool BulletMMOApp::ShouldClose(void)
{
    bool shouldClose = m_window->ShouldClose();
    return shouldClose;
}