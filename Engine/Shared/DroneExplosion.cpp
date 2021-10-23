#include "shared_stdafx.h"
#include "DroneExplosion.h"
#include "DroneSpriteAnimator.h"

void DroneExplosion::Awake()
{
	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->scale = Vec3::one() * 3.0f;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->material = m_material;
	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<DroneSpriteAnimator>();
}

void DroneExplosion::Update()
{

	m_animationTime += Time::DeltaTime();

	if (m_animationTime < 1.0f)
		m_animator->SetDefaultAnimation(m_animator->GetExplosion(), true);
	else
		gameObject->Destroy();

}

void DroneExplosion::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}

