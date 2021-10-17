#include "stdafx.h"
#include "LauncherGranade.h"
#include "PhysicsLayers.h"
#include "Monster.h"
#include "BillboardEffect.h"
#include "GranadeTrail.h"

void LauncherGranade::Awake()
{
	auto trailObj = CreateGameObjectToChild(transform);
	GranadeTrail* trail = trailObj->AddComponent<GranadeTrail>();

	m_rigidbody = gameObject->AddComponent<Rigidbody>();
	m_rigidbody->interpolate = Interpolate::Extrapolate;
	m_rigidbody->mass = 0.1f;
	m_rigidbody->positionIteration = 1;
	m_rigidbody->velocityIteration = 1;
	m_rigidbody->isContinousDetection = true;

	m_colliderObj = CreateGameObjectToChild(transform);
	m_colliderObj->transform->scale = Vec3::one() * 0.5f;
	m_collider = m_colliderObj->AddComponent<SphereCollider>();
	m_collider->layerIndex = (uint8_t)PhysicsLayers::Projectile;
	m_collider->restitutionCombineMode = PhysicsCombineMode::Average;
	m_collider->restitution = 0.5f;
	m_collider->friction = 0.5f;
	m_collider->SetIgnoreLayerBits(1 << (uint32_t)PhysicsLayers::Player);
	m_collider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &LauncherGranade::OnCollisionEnter);

	//auto colliderDebugRenderer = CreateGameObjectToChild(m_colliderObj->transform);
	//colliderDebugRenderer->transform->localPosition = Vec3(0.01f, 0.01f, 0);
	//colliderDebugRenderer->transform->scale = Vec3::one() * 0.5f;
	//m_colliderDebugRenderer = colliderDebugRenderer->AddComponent<UserMeshRenderer>();
	//m_colliderDebugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//m_colliderDebugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//m_colliderDebugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentRedTexture));

	//m_explosionDebugRendererObj = CreateGameObjectToChild(transform);
	//m_explosionDebugRendererObj->transform->scale = Vec3::one() * m_explosionRadius * 2.0f;
	//m_explosionDebugRenderer = m_explosionDebugRendererObj->AddComponent<UserMeshRenderer>();
	//m_explosionDebugRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//m_explosionDebugRenderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
	//m_explosionDebugRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));

	m_rendererObj = CreateGameObjectToChild(transform);
	m_rendererObj->transform->scale = Vec3::one() * 0.5f;
	m_renderer = m_rendererObj->AddComponent<UserMeshBillboardRenderer>();
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_renderer->material = Resource::FindAs<Material>(BuiltInAlphaTestMaterial);
	m_renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/launcher_effect/launcher_granade.png"));
}

void LauncherGranade::OnDestroy()
{
	m_collider->OnCollisionEnter -= Function<void(const CollisionEnter&)>(this, &LauncherGranade::OnCollisionEnter);
}

void LauncherGranade::Update()
{
	m_selfDestroyCounter -= Time::DeltaTime();

	if (m_selfDestroyCounter <= 0)
	{
		gameObject->Destroy();
	}

	if (m_groundCollision)
	{
		m_selfExplosionCounter -= Time::DeltaTime();
	}

	if (m_selfExplosionCounter <= 0)
	{
		Explosion();
	}
}

void LauncherGranade::OnCollisionEnter(const CollisionEnter& collider)
{
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
	{
		m_groundCollision = true;
	}
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Player)
	{
		Explosion();
	}
	if (collider.fromCollider->layerIndex == (uint8_t)PhysicsLayers::Monster)
	{
		Explosion();
	}
}

void LauncherGranade::Explosion()
{
	if (m_exploded)
	{
		return;
	}

	m_exploded = true;

	GameObject* effectObj = CreateGameObject();
	effectObj->transform->position = transform->position;
	effectObj->transform->scale = Vec3::one() * 4.0f;

	BillboardEffect* effect = effectObj->AddComponent<BillboardEffect>();
	effect->AddTexture(L"../SharedResource/Texture/explosion0/0.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/1.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/2.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/3.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/4.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/5.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/6.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/7.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/8.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/9.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/10.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/11.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/12.png");
	effect->AddTexture(L"../SharedResource/Texture/explosion0/13.png");

	auto overlapVector = Physics::OverlapSphereAll(
		transform->position,
		m_explosionRadius,
		(1 << (int)PhysicsLayers::Monster),
		PhysicsQueryType::All,
		64,
		m_rigidbody
	);

	for (auto& monsterCollider : overlapVector)
	{
		Monster* monster = monsterCollider->rigidbody->gameObject->GetComponent<Monster>();

		Vec3 direction = monster->transform->position - transform->position;
		direction.y = 0;
		direction.Normalize();

		DamageParameters params;
		params.monsterHitCollider = monsterCollider;
		params.damageType = MonsterDamageType::Explosion;
		params.damage = float(m_explosionDamage);
		params.force = direction * 30;
		params.includeDamageDirection = true;
		params.damageDirection = direction;
		params.includeAttackBeginPoint = true;
		params.attackBeginPoint = transform->position;

		monster->TakeDamage(params);
	}

	gameObject->Destroy();
}

Rigidbody* LauncherGranade::GetRigidbody() const
{
	return m_rigidbody;
}
