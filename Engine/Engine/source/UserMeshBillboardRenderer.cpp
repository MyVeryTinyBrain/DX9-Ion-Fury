#include "EngineBase.h"
#include "UserMeshBillboardRenderer.h"
#include "Transform.h"
#include "GraphicDevice.h"
#include "UserMesh.h"
#include "Camera.h"

void UserMeshBillboardRenderer::Render()
{
    Renderer::Render();

    if (!m_userMesh) return;

    Camera* mainCamera = Camera::GetMainCamera();

    if (!mainCamera) return;

    Vec3 camEulerAngle = mainCamera->transform->eulerAngle;

    if (m_freezeX) camEulerAngle.x = 0;
    if (m_freezeY) camEulerAngle.y = 0;
    if (m_freezeZ) camEulerAngle.z = 0;

    Vec3 gameObjectEulerAngle = transform->eulerAngle;

    if (m_ignoreRotationX) gameObjectEulerAngle.x = 0;
    if (m_ignoreRotationY) gameObjectEulerAngle.y = 0;
    if (m_ignoreRotationZ) gameObjectEulerAngle.z = 0;

    const Mat4& localToWorld = 
        Mat4::SRT(
            transform->scale, 
            (gameObjectEulerAngle + camEulerAngle) * Deg2Rad,
            transform->position);

    GraphicDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &localToWorld);

    m_userMesh->Draw();
}

void UserMeshBillboardRenderer::SetFreezeX(bool value)
{
    m_freezeX = value;
}

void UserMeshBillboardRenderer::SetFreezeY(bool value)
{
    m_freezeY = value;
}

void UserMeshBillboardRenderer::SetFreezeZ(bool value)
{
    m_freezeZ = value;
}

bool UserMeshBillboardRenderer::IsXFrozen() const
{
    return m_freezeX;
}

bool UserMeshBillboardRenderer::IsYFrozen() const
{
    return m_freezeY;
}

bool UserMeshBillboardRenderer::IsZFrozen() const
{
    return m_freezeZ;
}

void UserMeshBillboardRenderer::SetIgnoreRotationX(bool value)
{
    m_ignoreRotationX = value;
}

void UserMeshBillboardRenderer::SetIgnoreRotationY(bool value)
{
    m_ignoreRotationY = value;
}

void UserMeshBillboardRenderer::SetIgnoreRotationZ(bool value)
{
    m_ignoreRotationZ = value;
}

bool UserMeshBillboardRenderer::IsIgnoreRotationX() const
{
    return m_ignoreRotationX;
}

bool UserMeshBillboardRenderer::IsIgnoreRotationY() const
{
    return m_ignoreRotationY;
}

bool UserMeshBillboardRenderer::IsIgnoreRotationZ() const
{
    return m_ignoreRotationZ;
}
