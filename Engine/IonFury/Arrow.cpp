#include "stdafx.h"
#include "Arrow.h"
#include "PhysicsLayers.h"
#include "Monster.h"
#include "TrailRenderer.h"

void Arrow::Awake()
{
	m_trailRenderer = gameObject->AddComponent<TrailRenderer>();
	m_trailRenderer->width = 0.2f;
	m_trailRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInRedTexture));

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
	m_renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInRedTexture));
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

void Arrow::LateUpdate()
{
	if (m_rigidbody)
	{
		m_trailRenderer->AddPoint(transform->position);

		if (m_trailRenderer->GetPointCount() > 50)
		{
			m_trailRenderer->RemoveFirstPoint();
		}
	}
	else
	{
		m_trailRenderer->RemoveFirstPoint();

		if (!m_hitOnTerrain && m_trailRenderer->GetPointCount() == 0)
		{
			gameObject->Destroy();
		}
	}
}

void Arrow::OnCollisionEnter(const CollisionEnter& collider)
{
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
	{
		transform->position = collider.GetContact(0).point + collider.GetContact(0).normal * 0.1f;
		m_hitOnTerrain = true;
		RemoveBodyAndCollider();
	}
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Player)
	{
		RemoveBodyAndCollider();
		RemoveRenderer();
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

		RemoveBodyAndCollider();
		RemoveRenderer();
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

void Arrow::RemoveRenderer()
{
	if (m_renderer)
	{
		m_renderer->Destroy();
		m_renderer = nullptr;
	}
}
