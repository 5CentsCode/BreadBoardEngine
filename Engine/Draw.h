#include "Typedefs.h"
#include "DataType/Model.h"
#include "Components/Camera.h"
#include "Components/Transform.h"

class Draw
{
public:

    static void SetCamera(Component::Camera* camera, Component::Transform* cameraTransform);

    static void DrawModel(Model& model, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale, const Color& color);
    static void DrawBillboard(Model& model, const glm::vec3& position, const float& rotation, const glm::vec3& scale, const Color& color);

private:

    static void DrawMesh(const Mesh& mesh, const Material& material, const glm::mat4x4 transform);

    static glm::mat4x4 GetCameraViewMatrix();
    static glm::mat4x4 GetCameraProjectionMatrix();

private:

    static Component::Camera* m_camera;
    static Component::Transform* m_cameraTransform;
};