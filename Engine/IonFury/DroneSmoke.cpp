#include "stdafx.h"
#include "DroneSmoke.h"
#include "DroneSpriteAnimator.h"

void DroneSmoke::Awake()
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

void DroneSmoke::Update()
{
	m_animationTime += Time::DeltaTime();

	if (m_animationTime < 1.2f)
		m_animator->SetDefaultAnimation(m_animator->GetSmoke(), true);
	else
		Destroy();
}

void DroneSmoke::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}
