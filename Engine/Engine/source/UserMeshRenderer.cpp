#include "EngineBase.h"
#include "UserMeshRenderer.h"
#include "Transform.h"
#include "GraphicDevice.h"
#include "UserMesh.h"

void UserMeshRenderer::Render()
{
    Renderer::Render();

    if (!m_userMesh) return;

    const Mat4& localToWorld = transform->localToWorld;

    GraphicDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &localToWorld);

    m_userMesh->Draw();
}

bool UserMeshRenderer::Raycast(Vec3& hitPoint, const Vec3& worldRayPoint, const Vec3& worldRayDir)
{
    if (!m_userMesh)
        return false;

	return m_userMesh->Raycast(hitPoint, worldRayPoint, worldRayDir, transform->localToWorld);
}

void UserMeshRenderer::SetUserMesh(const Ref<UserMesh>& userMesh)
{
    m_userMesh = userMesh;
}

const Ref<UserMesh>& UserMeshRenderer::GetUserMesh() const
{
    return m_userMesh;
}
