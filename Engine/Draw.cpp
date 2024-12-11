#include "Draw.h"
#include <glad/glad.h>

Component::Camera* Draw::m_camera;
Component::Transform* Draw::m_cameraTransform;

void Draw::SetCamera(Component::Camera* camera, Component::Transform* cameraTransform)
{
    m_camera = camera;
    m_cameraTransform = cameraTransform;
}

void Draw::DrawModel(Model& model, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale, const Color& color)
{
    REFERENCE(color);

    Component::Transform modelTransform;
    modelTransform.SetPosition(position);
    modelTransform.SetScale(scale);
    modelTransform.SetRotation(rotation);

    glm::mat4x4 meshTransform = Draw::GetCameraProjectionMatrix() * Draw::GetCameraViewMatrix() * modelTransform.GetWorldMatrix();

    for (Mesh mesh : model.Meshes)
    {
        DrawMesh(mesh, model.Materials.front(), meshTransform);
    }
}

void Draw::DrawBillboard(Model& model, const glm::vec3& position, const float& rotation, const glm::vec3& scale, const Color& color)
{
    glm::quat modelRotation = glm::angleAxis(glm::radians(rotation), m_cameraTransform->GetForward());
    glm::quat cameraRotation = m_cameraTransform->GetRotation();
    glm::quat offsetRotation = glm::angleAxis(glm::radians(90.0f), VEC3_RIGHT);
    glm::quat finalRotation = modelRotation * cameraRotation * offsetRotation;

    DrawModel(model, position, finalRotation, scale, color);
}

void Draw::DrawMesh(const Mesh& mesh, const Material& material, const glm::mat4x4 transform)
{
    material.Shader.Bind();
    glBindVertexArray(mesh.VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[0]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[1]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[4]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.VboIds[5]);
    glBindTexture(GL_TEXTURE_2D, material.Texture.Id);

    material.Shader.SetUniform("texture0", material.Texture.Id);
    material.Shader.SetUniform("colDiffuse", Color(1.0f));
    material.Shader.SetUniform("mvp", transform);

    glDrawElements(GL_TRIANGLES, (int32)mesh.Indices.size(), GL_UNSIGNED_SHORT, 0);
}

glm::mat4x4 Draw::GetCameraViewMatrix()
{
    glm::vec3 position = m_cameraTransform->GetPosition();
    glm::vec3 forward = m_cameraTransform->GetForward();
    glm::vec3 up = m_cameraTransform->GetUp();

    glm::mat4x4 viewMatrix = glm::lookAt(position, position + forward, up);

    return viewMatrix;
}

glm::mat4x4 Draw::GetCameraProjectionMatrix()
{
    glm::mat4x4 projectionMatrix = m_camera->GetProjectionMatrix();
    return projectionMatrix;
}