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

    const Mat4& localToWorld = Mat4::SRT(transform->scale, (transform->eulerAngle + mainCamera->transform->eulerAngle) * Deg2Rad, transform->position);

    GraphicDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &localToWorld);

    m_userMesh->Draw();
}
