#include "stdafx.h"
#include "WarmechBullet.h"
#include "WarmechSpriteAnimator.h"

void WarmechBullet::Awake()
{
	m_moveSpeed = 3.0f;

	m_body = gameObject->AddComponent<Rigidbody>();
	m_body->SetRotationLockAxis(PhysicsAxis::All, true);

	m_body->mass = 0.01f;
	m_body->interpolate = true;
	m_body->useGravity = false;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localPosition = Vec3(0, 1.f, 0);
	m_rendererObj->transform->localScale = Vec3::one() * 0.5f;

	

	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;


	m_animator = m_rendererObj->AddComponent<WarmechSpriteAnimator>();
}

void WarmechBullet::Update()
{

	m_animator->SetDefaultAnimation(m_animator->GetBullet(), true);

	transform->position += transform->forward * m_moveSpeed * Time::DeltaTime();

}

void WarmechBullet::LateUpdate()
{
}

void WarmechBullet::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}
