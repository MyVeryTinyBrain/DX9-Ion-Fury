#include "stdafx.h"
#include "WarmechHit.h"
#include "WarmechSpriteAnimator.h"
#include "PhysicsLayers.h"

void WarmechHit::Awake()
{
	m_moveSpeed = 3.0f;

	m_body = gameObject->AddComponent<Rigidbody>();
	m_body->SetRotationLockAxis(PhysicsAxis::All, true);

	m_body->mass = 0.01f;
	m_body->interpolate = Interpolate::Extrapolate;


	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localScale = Vec3::one() * 0.5f;


	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;

	m_animator = m_rendererObj->AddComponent<WarmechSpriteAnimator>();

}

void WarmechHit::FixedUpdate()
{
	PhysicsRay ray(transform->position, Vec3::down(), sqrtf(0.3f));
	RaycastHit hit;

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider, m_body))
	{

		if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
		{
			m_ground = true;
		}
	}
}

void WarmechHit::Update()
{
	//m_animator->SetDefaultAnimation(m_animator->GetDamage(), true);
	m_animator->SetDefaultAnimation(m_animator->GetSpriteAnimation(SPRITE_WARMECH::Damage), true);


	if (m_ground)
	{
		m_body->SetRotationLockAxis(PhysicsAxis::All, true);
		m_body->SetTranslationLockAxis(PhysicsAxis::All, true);
	}
	else
		transform->position += Vec3::down() * m_moveSpeed * Time::DeltaTime();

	m_selfDestroyCounter -= Time::DeltaTime();

	if (m_selfDestroyCounter < 0)
	{
		gameObject->Destroy();
	}
}

void WarmechHit::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}
