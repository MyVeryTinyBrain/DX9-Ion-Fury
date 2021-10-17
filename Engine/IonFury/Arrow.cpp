#include "stdafx.h"
#include "Arrow.h"
#include "PhysicsLayers.h"
#include "Monster.h"

void Arrow::Awake()
{
	m_rigidbody = gameObject->AddComponent<Rigidbody>();
	m_rigidbody->interpolate = Interpolate::Extrapolate;
	m_rigidbody->mass = 0.1f;
	m_rigidbody->positionIteration = 1;
	m_rigidbody->velocityIteration = 1;
	m_rigidbody->isContinousDetection = true;
	m_rigidbody->SetRotationLockAxis(PhysicsAxis::All, true);

	m_colliderObj = CreateGameObjectToChild(gameObject->transform);
	m_colliderObj->transform->localScale = Vec3(0.05f, 0.05f, 1.0f);
	m_collider = m_colliderObj->AddComponent<BoxCollider>();
	m_collider->layerIndex = (uint8_t)PhysicsLayers::Projectile;
	m_collider->SetIgnoreLayerBits(1 << (uint32_t)PhysicsLayers::Player);
	m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &Arrow::OnCollisionEnter);

	//auto colliderDebugRenderer = CreateGameObjectToChild(m_colliderObj->transform);
	//colliderDebugRenderer->transform->localPosition = Vec3(0.01f, 0.01f, 0);
	//m_colliderDebugRenderer = colliderDebugRenderer->AddComponent<UserMeshRenderer>();
	//m_colliderDebugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
	//m_colliderDebugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//m_colliderDebugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));

	m_rendererObj = CreateGameObjectToChild(gameObject->transform);
	m_rendererObj->transform->localScale = Vec3(0.05f, 1.0f, 0.05f);
	m_rendererObj->transform->localEulerAngle = Vec3(90, 0, 0);
	m_renderer = m_rendererObj->AddComponent<UserMeshRenderer>();
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCyilinderUserMesh);
	m_renderer->material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
	m_renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInGreenTexture));
}

void Arrow::Start()
{
	m_beginPoint = transform->position;
}

void Arrow::OnDestroy()
{
	RemoveBodyAndCollider();
}

void Arrow::FixedUpdate()
{
}

void Arrow::Update()
{
	m_selfDestroyCounter -= Time::DeltaTime();

	if (m_selfDestroyCounter <= 0)
	{
		gameObject->Destroy();
	}
}

void Arrow::OnCollisionEnter(const CollisionEnter& collider)
{
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
	{
		transform->position = collider.GetContact(0).point + collider.GetContact(0).normal * 0.1f;

		RemoveBodyAndCollider();
	}
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Player)
	{
		gameObject->Destroy();
	}
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Monster)
	{
		Monster* monster = collider.fromCollider->rigidbody->gameObject->GetComponent<Monster>();

		if (!monster)
		{
			return;
		}

		Vec3 direction = transform->forward;
		direction.y = 0;
		direction.Normalize();

		DamageParameters params;
		params.monsterHitCollider = collider.fromCollider;
		params.damageType = MonsterDamageType::Bullet;
		params.damage = float(m_damage);
		params.force = transform->forward * 40;
		params.includeDamageDirection = true;
		params.damageDirection = transform->forward;
		params.includeAttackBeginPoint = true;
		params.attackBeginPoint = m_beginPoint;
		params.includeMonsterHitWorldPoint = true;
		params.monsterHitWorldPoint = collider.GetContact(0).point;

		monster->TakeDamage(params);

		gameObject->Destroy();
	}
}

Rigidbody* Arrow::GetRigidbody() const
{
	return m_rigidbody;
}

void Arrow::RemoveBodyAndCollider()
{
	if (m_collider)
	{
		m_collider->OnCollisionEnter -= Function<void(const CollisionEnter&)>(this, &Arrow::OnCollisionEnter);

		m_colliderObj->Destroy();

		m_collider = nullptr;
	}

	if (m_rigidbody)
	{
		m_rigidbody->Destroy();

		m_rigidbody = nullptr;
	}
}
