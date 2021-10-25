#include "shared_stdafx.h"
#include "DeaconflyEffect.h"
#include "DeaconSpriteAnimator.h"

void DeaconflyEffect::Awake()
{
	auto m_rendereObj = CreateGameObjectToChild(transform);
	m_rendereObj->transform->scale = Vec3::one() * m_scail;

	m_rendereObj->transform->localPosition = Vec3(0, -3, 0);


	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_renderer = m_rendereObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->material = m_material;
	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendereObj->AddComponent<DeaconSpriteAnimator>();
}

void DeaconflyEffect::Update()
{
	m_animationTime += Time::DeltaTime();
	scailminusTime += Time::DeltaTime();

	if (scailminusTime > 0.05f)
	{
		gameObject->Destroy();
	}
	if (m_animationTime < 0.5f)
		m_animator->SetDefaultAnimation(m_animator->GetSmoke(), true);

}

void DeaconflyEffect::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}
