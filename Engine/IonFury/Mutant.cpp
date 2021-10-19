#include "stdafx.h"
#include "Mutant.h"
#include "MutantSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"

void Mutant::Awake()
{
	Monster::Awake();

	m_hp = 10;
	m_moveSpeed = 2.0f;

	m_body->mass = 0.5f;
	m_body->interpolate = Interpolate::Extrapolate;
	m_body->useGravity = false;


	m_rendererObj->transform->scale = Vec3::one() * 3.0f;
	m_rendererObj->transform->localPosition = Vec3(0, 0.f, 0);

	m_renderer = CreateRenderer();

	m_animator = m_renderer->gameObject->AddComponent<MutantSpriteAnimator>();
}

void Mutant::FixedUpdate()
{
	Monster::FixedUpdate();

	MoveToTarget();

	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Mutant::Update()
{
	Monster::Update();
}

void Mutant::OnDestroy()
{
	Monster::OnDestroy();
}

Collider* Mutant::InitializeCollider(GameObject* colliderObj)
{
	{
		auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	}

	colliderObj->transform->localScale = Vec3::one() * 1.25f;

	return colliderObj->AddComponent<SphereCollider>();
}

void Mutant::OnDamage(DamageParameters& params)
{
	m_hasTargetCoord = false;

	switch (params.damageType)
	{
	case MonsterDamageType::Bullet:
		m_moveSpeed = 0.f;
		break;
	case MonsterDamageType::Explosion:
		m_moveSpeed = 0.f;
		break;
	case MonsterDamageType::Zizizik:
		//m_animator->SetDefaultAnimation(m_animator->GetDamage(), true);
		break;
	}

	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
	{
		GameObject* bloodEffectObj = CreateGameObject();
		bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
		bloodEffectObj->AddComponent<BloodEffect>();
	}

	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& gunnerPos = transform->position;
	Vec3 forward = playerPos - gunnerPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
}

void Mutant::OnDead(bool& dead, DamageParameters& params)
{
	//m_body->useGravity = true;
	m_hasTargetCoord = false;
	m_attackCount = 0;

	int dieIndex = rand() % (int)MutantSpriteAnimator::DIE_MUTANT::MAX;


	if (params.damageType == MonsterDamageType::Explosion)
	{
		dieIndex = (int)MonsterDamageType::Explosion;
	}

	m_animator->PlayDie((MutantSpriteAnimator::DIE_MUTANT)dieIndex);
}

void Mutant::MoveToTarget()
{
	if (!m_hasTargetCoord)
		return;

	const Vec3& spiderPos = transform->position;
	Vec3 forward = m_targetCoord - spiderPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;

	Vec3 xzSpiderPos = Vec3(spiderPos.x, 0, spiderPos.z);
	float distance = Vec3::Distance(xzSpiderPos, m_targetCoord);

	if (distance > 2.1f)
	{
		PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
		RaycastHit hit;

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
		{
			float angle = Vec3::Angle(hit.normal, Vec3::up());

			if (hit.collider->layerIndex == (PxU32)PhysicsLayers::Terrain && angle > 85 && angle < 95)
			{
				m_hasTargetCoord = false;
				return;
			}
			else if (hit.collider->layerIndex == (PxU32)PhysicsLayers::Monster)
			{
				m_hasTargetCoord = false;
				return;
			}
		}

		Vec3 velocity = forward * m_moveSpeed;
		velocity.y = m_body->velocity.y;
		m_body->velocity = velocity;


		if (Vec3::Distance(xzSpiderPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
		{
			m_hasTargetCoord = false;
			return;
		}

		m_beforeCoord = transform->position;
		m_beforeCoord.y = 0;

	}
	else
	{
		m_hasTargetCoord = false;
	}
}

void Mutant::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;
}

void Mutant::Attack()
{
	if (m_attackCount > 0)
	{
		--m_attackCount;

		//// °Å¹ÌÁÙ 
		//auto obj = CreateGameObject();
		//obj->transform->position = transform->position + transform->forward;// *2.f;
		//obj->transform->forward = transform->forward;
		//obj->AddComponent<Web>();

	}
}
void Mutant::ShootToPlayer()
{
	Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayer.Normalize();
	Player::GetInstance()->TakeDamage(1);
}