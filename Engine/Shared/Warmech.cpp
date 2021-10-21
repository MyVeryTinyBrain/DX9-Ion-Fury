#include "shared_stdafx.h"
#include "Warmech.h"
#include "WarmechSpriteAnimator.h"
#include "BloodEffect.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "WarmechBullet.h"
#include "WarmechMissile.h"
#include "WarmechHit.h"
#include "WarmechExplosion.h"

void Warmech::Awake()
{
	Monster::Awake();

	m_hp = 50;
	m_moveSpeed = 3.0f;

	m_body->mass = 8.f;
	m_body->interpolate = Interpolate::Extrapolate;

	{
		auto renderer = CreateRenderer();
		m_bodyWarmech = renderer->gameObject;

		renderer->freezeX = true;
		renderer->freezeZ = true;
		renderer->material = m_material;
		renderer->userMesh = m_quad;

		renderer->transform->localPosition = Vec3(0, 3.25f, 0.f);
		renderer->transform->scale = Vec3::one() * 4.0f;

		m_bodyAnimator = m_bodyWarmech->AddComponent<WarmechSpriteAnimator>();
	}

	{
		auto renderer = CreateRenderer();
		m_legWarmech = renderer->gameObject;
		m_legWarmech->transform->parent = m_bodyWarmech->transform;

		renderer->freezeX = true;
		renderer->freezeZ = true;
		renderer->material = m_material;
		renderer->userMesh = m_quad;

		renderer->transform->localPosition = Vec3(0, -0.35f, 0.f);
		renderer->transform->scale = Vec3::one() * 5.0f;

		m_legAnimator = m_legWarmech->AddComponent<WarmechSpriteAnimator>();
	}
}

void Warmech::FixedUpdate()
{
	Monster::FixedUpdate();

	if (Time::FixedTimeScale() == 0)
		return;

	if (m_isDead)
	{
		return;
	}

	MoveToTarget();

	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Warmech::Update()
{
	Monster::Update();

	m_bodyAnimator->SetAngle(AngleToPlayerWithSign());

	if (Time::TimeScale() == 0)
		return;

	if (m_isDead)
	{
		if (m_body)
		{
			m_body->Destroy();
			m_collider->Destroy();
			m_body = nullptr;
			m_collider = nullptr;
		}
		return;
	}

	AttackType attackType = (AttackType)(rand() % unsigned int(AttackType::Max));

	if (!m_attacking && (m_breakTime <= 0))
	{
		actionType = (ActionType)(rand() % unsigned int(ActionType::Max));
		SetAction(actionType, attackType);
	}

	if (m_breakTime > 0 && m_bodyAnimator->IsPlayingIdle())
	{
		m_breakTime -= Time::DeltaTime();
	}

	if (m_bodyAnimator->IsPlayingIdle() && m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
	{
		m_legAnimator->PlayWalk();
	}
	else if (m_legAnimator->IsPlayingWalk() && m_body->velocity.magnitude() < m_moveSpeed * 0.5f)
	{
		m_bodyAnimator->PlayDefaultAnimation();
		m_legAnimator->PlayWalkIdle();
	}


	Attack();


	if (m_bodyAnimator->IsPlayingShoot() | m_bodyAnimator->IsPlayingMissile())
	{
		m_defaultEmissive = Color::white();
	}
	else
	{
		m_defaultEmissive = Color::black();
	}
}

void Warmech::OnDestroy()
{
	Monster::OnDestroy();

	if (Time::TimeScale() == 0)
		return;
}

Collider* Warmech::InitializeCollider(GameObject* colliderObj)
{
	//{
	//	auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}

	m_capsuleCollider = colliderObj->AddComponent<CapsuleCollider>();
	m_capsuleCollider->transform->localScale = Vec3::one() * 1.6f;

	return m_capsuleCollider;
}

void Warmech::OnDamage(DamageParameters& params)
{
	m_hasTargetCoord = false;
	m_attackCount = 5;
	m_breakTime = 0.35f;

	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
	{
		{
			GameObject* bloodEffectObj = CreateGameObject();
			bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
			bloodEffectObj->AddComponent<BloodEffect>();
		}
		{
			GameObject* bloodEffectObj = CreateGameObject();
			bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
			bloodEffectObj->AddComponent<WarmechHit>();
		}
	}


	params.force = Vec3::zero();

	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& warmehPos = transform->position;
	Vec3 forward = playerPos - warmehPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
}

void Warmech::OnDead(bool& dead, DamageParameters& params)
{

	Explosion();

	gameObject->Destroy();
}

void Warmech::MoveToTarget()
{
	if (!m_hasTargetCoord)
	{
		return;
	}

	const Vec3& warmechPos = transform->position;

	Vec3 forward = m_targetCoord - warmechPos;
	forward.y = 0;
	forward.Normalize();

	transform->forward = forward;

	Vec3 xzWarmechPos = Vec3(warmechPos.x, 0, warmechPos.z);

	float distance = Vec3::Distance(xzWarmechPos, m_targetCoord);

	if (distance > 2.1f)
	{

		PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
		RaycastHit hit;

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
		{
			float angle = Vec3::Angle(hit.normal, Vec3::up());

			if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain && angle > 85 && angle < 95)
			{
				m_hasTargetCoord = false;
				return;
			}
			else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
			{
				m_hasTargetCoord = false;
				return;
			}
		}

		Vec3 acceleration = forward * m_moveSpeed;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
		velocity.y = m_body->velocity.y;
		m_body->velocity = velocity;

		if (Vec3::Distance(xzWarmechPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
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

void Warmech::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;
}

void Warmech::Explosion()
{
	{
		GameObject* effectObj = CreateGameObject();
		effectObj->transform->position = Vec3(transform->position.x, transform->position.y + 0.35f, transform->position.z);
		effectObj->AddComponent<WarmechExplosion>();
	}
	{
		GameObject* effectObj = CreateGameObject();
		effectObj->transform->position = Vec3(transform->position.x, transform->position.y - 0.8f, transform->position.z);
		effectObj->AddComponent<WarmechExplosion>();
	}
}

void Warmech::Attack()
{
	if (m_bodyAnimator->IsPlayingShoot() | m_bodyAnimator->IsPlayingMissile())
	{
		return;
	}

	if (m_attackCount > 0)
	{
		

		switch (actionType)
		{
		case Warmech::ActionType::Bullet:
		{
			--m_attackCount;
			m_bodyAnimator->PlayShoot();

			auto obj = CreateGameObject();
			obj->transform->position = Vec3(transform->position.x, transform->position.y + 0.45f , transform->position.z) + (-transform->right);
			obj->AddComponent<WarmechBullet>();
		}
		break;
		case Warmech::ActionType::Missile:
		{
			--m_attackCount;
			m_bodyAnimator->PlayMissile();

			auto obj = CreateGameObject();
			obj->transform->position = Vec3(transform->position.x, transform->position.y + 0.45f, transform->position.z) + transform->right;
			obj->AddComponent<WarmechMissile>();
		}
		break;
		}

		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

		ShootToPlayer();
	}
	else
		m_attacking = false;
}

void Warmech::SetAction(ActionType type, AttackType attacktype)
{
	m_hasTargetCoord = false;
	m_attackCount = 0;
	m_breakTime = 0.35f;

	switch (type)
	{
	case ActionType::Idle:
	{

	}
	break;
	case ActionType::WalkToRandomCoord:
	{
		float randomRadian = (rand() % 360) * Deg2Rad;
		float randomDistance = (rand() % 15) + 2.1f + 0.1f;
		Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
		SetTargetCoord(targetCoord);
	}
	break;
	case ActionType::WalkToPlayerDirection:
	{
		const Vec3& monsterPos = transform->position;
		const Vec3& playerPos = Player::GetInstance()->transform->position;
		Vec3 relative = playerPos - monsterPos;
		float distance = Clamp(relative.magnitude(), 0, 8.0f);
		Vec3 direction = relative.normalized();
		SetTargetCoord(monsterPos + direction * distance);
	}
	break;
	case ActionType::Bullet:
	{		
		if (m_bodyAnimator->IsPlayingMissile())
			return;
		m_attackCount = 10;
		m_attacking = true;
	}
	case ActionType::Missile:
	{
		if (m_bodyAnimator->IsPlayingShoot())
			return;
		m_attackCount = 1;
		m_attacking = true;
	}
	break;
	}
}
void Warmech::ShootToPlayer()
{
	Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayer.Normalize();
	Player::GetInstance()->TakeDamage(1);
}