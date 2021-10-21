#include "shared_stdafx.h"
#include "Web.h"
#include "Player.h"
#include "SpiderSpriteAnimator.h"
#include "PhysicsLayers.h"

void Web::Awake()
{

	m_moveSpeed = 2.0f;

	m_body = gameObject->AddComponent<Rigidbody>();
	m_body->SetRotationLockAxis(PhysicsAxis::All, true);

	m_body->mass = 0.01f;
	m_body->interpolate = Interpolate::Extrapolate;

	MaterialParameters params;
	params.alphaTest = true;
	params.renderQueue = RenderQueue::AlphaTest;
	m_material = Material::CreateUnmanaged(params);

	auto m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->localPosition = Vec3(0, 1.f, 0);
	m_rendererObj->transform->scale = Vec3::one() * 3.0f;

	auto m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;
	m_renderer->material = m_material;

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;


	m_animator = m_rendererObj->AddComponent<SpiderSpriteAnimator>();

}

void Web::Update()
{

	m_animationtime += Time::DeltaTime();

	if (m_animationtime < 0.4f)
	{
		m_animator->SetDefaultAnimation(m_animator->GetWeb(), true);


		m_body->SetRotationLockAxis(PhysicsAxis::All, true);
		m_body->SetTranslationLockAxis(PhysicsAxis::All, true);

		Vec3 velocity = transform->forward * m_moveSpeed;
		m_body->velocity = velocity;

		transform->position += transform->forward * m_moveSpeed * Time::DeltaTime();
	}
	else
	{
		m_animator->Pause();
	}

	AttackToPlayer();

}

void Web::LateUpdate()
{
	if (m_animationtime > 3.f)
		gameObject->Destroy();
}

void Web::OnDestroy()
{
	m_material->ReleaseUnmanaged();
	m_quad->ReleaseUnmanaged();
}

void Web::AttackToPlayer()
{

	Vec3 webToPlayerDir = Player::GetInstance()->transform->position - transform->position;
	webToPlayerDir.y = 0;
	webToPlayerDir.Normalize();

	RaycastHit hit;
	PhysicsRay ray(transform->position, webToPlayerDir, sqrtf(0.1f));

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::All, m_body))
	{
		if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{
			Player::GetInstance()->TakeDamage(1);
		}
	}

}

