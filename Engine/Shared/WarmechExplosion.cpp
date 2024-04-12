#include "shared_stdafx.h"
#include "WarmechExplosion.h"
#include "WarmechSpriteAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"

void WarmechExplosion::Awake()
{
	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->scale = Vec3::one() * 2.5f;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	params.useLight = false;
	m_material = Material::CreateUnmanaged(params);

	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->material = m_material;
	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<WarmechSpriteAnimator>();
}

void WarmechExplosion::Update()
{
	m_animationTime += Time::DeltaTime();

	if (m_animationTime < 1.2f)
		m_animator->SetDefaultAnimation(m_animator->GetSpriteAnimation(SPRITE_WARMECH::Explosion), true);
	else
		gameObject->Destroy();
}

void WarmechExplosion::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();

}
