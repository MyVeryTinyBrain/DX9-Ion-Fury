#include "shared_stdafx.h"
#include "Web.h"
#include "Player.h"
#include "WebSpriteAnimator.h"
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

	m_colliderObj = CreateGameObjectToChild(gameObject->transform);
	m_collider = m_colliderObj->AddComponent<BoxCollider>();
	m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &Web::OnCollisionEnter);


	//auto colliderDebugRenderer = CreateGameObjectToChild(m_colliderObj->transform);
	////colliderDebugRenderer->transform->localPosition = Vec3(0.01f, 0.01f, 0);
	//auto m_colliderDebugRenderer = colliderDebugRenderer->AddComponent<UserMeshRenderer>();
	//m_colliderDebugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//m_colliderDebugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//m_colliderDebugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));

	m_quad = UserMesh::CreateUnmanaged<QuadUserMesh>();
	m_renderer->userMesh = m_quad;


	m_animator = m_rendererObj->AddComponent<WebSpriteAnimator>();

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

	//AttackToPlayer();

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

	if (m_collider)
	{
		m_collider->OnCollisionEnter -= Function<void(const CollisionEnter&)>(this, &Web::OnCollisionEnter);

		m_collider->Destroy();

		m_collider = nullptr;
	}

	if (m_body)
	{
		m_body->Destroy();

		m_body = nullptr;
	}
}

void Web::OnCollisionEnter(const CollisionEnter& collider)
{
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Player)
	{
		Player::GetInstance()->TakeDamage(1);
	}
}
