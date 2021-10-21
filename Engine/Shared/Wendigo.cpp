#include "shared_stdafx.h"
#include "Wendigo.h"
#include "WendigoSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"

void Wendigo::Awake()
{
	Monster::Awake();

	m_hp = 10;
	m_moveSpeed = 3.0f;

	m_body->mass = 5.f;
	m_body->interpolate = Interpolate::Extrapolate;


	m_rendererObj->transform->scale = Vec3::one() * 8.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -1.f, 0);

	m_renderer = CreateRenderer();

	m_animator = m_renderer->gameObject->AddComponent<WendigoSpriteAnimator>();
}

void Wendigo::FixedUpdate()
{
	Monster::FixedUpdate();

	m_animator->SetAngle(AngleToPlayerWithSign());

	if (Time::FixedTimeScale() == 0)
		return;

	if (m_isDead)
	{
		return;
	}

	MoveToTarget();


	JumpCheck();



	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Wendigo::Update()
{
	Monster::Update();

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

	Jump();

	Attack();

	m_PatternTime += Time::DeltaTime();

	if (m_PatternTime > 3.f)
	{
		actionType = (ActionType)(rand() % unsigned int(ActionType::Max));
		SetAction(actionType);
		m_PatternTime = 0.f;
	}
}

void Wendigo::LateUpdate()
{
	Monster::LateUpdate();

}

void Wendigo::OnDestroy()
{
	Monster::OnDestroy();

	if (Time::TimeScale() == 0)
		return;
}

Collider* Wendigo::InitializeCollider(GameObject* colliderObj)
{
	{
		auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);

	}
	m_capsuleCollider = colliderObj->AddComponent<CapsuleCollider>();


	return m_capsuleCollider;
}

void Wendigo::OnDamage(DamageParameters& params)
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
		m_animator->PlayDamage();
		break;
	}

	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
	{
		GameObject* bloodEffectObj = CreateGameObject();
		bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
		bloodEffectObj->AddComponent<BloodEffect>();
	}

	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& wendigoPos = transform->position;
	Vec3 forward = playerPos - wendigoPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;

	//params.force = Vec3::zero();
}

void Wendigo::OnDead(bool& dead, DamageParameters& params)
{
	m_hasTargetCoord = false;
	m_attackCount = 0;

	m_animator->PlayDie();
}

void Wendigo::MoveToTarget()
{
	if (!m_hasTargetCoord)
		return;

	const Vec3& wendigoPos = transform->position;
	Vec3 forward = m_targetCoord - wendigoPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;

	Vec3 xzWendigoPos = Vec3(wendigoPos.x, 0, wendigoPos.z);
	float distance = Vec3::Distance(xzWendigoPos, m_targetCoord);

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


		if (Vec3::Distance(xzWendigoPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
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
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}

}

void Wendigo::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;
}

void Wendigo::Jump()
{
	if (m_hasJump)		// มกวม
	{
		Vec3 playerPos = Player::GetInstance()->transform->position;
		Vec3 monsterPos = transform->position;

		Vec3 forward = playerPos - monsterPos;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

		Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

		Vec3 velocity = Quat::AxisAngle(right, -22.5f) * forward * m_moveSpeed;

		transform->position += velocity * Time::DeltaTime() * 2.5f;

		m_animator->PlayJump();

		AttackToPlayer();

		if (transform->position.y > m_jumpY + 1.f)
		{
			m_hasJump = false;
			m_animator->PlayWalk();
		}
	}
}

void Wendigo::JumpCheck()
{
	if (!m_animator->IsPlayingWalk())
		return;

	Vec3 mosterToPlayerDir = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayerDir.y = 0;
	mosterToPlayerDir.Normalize();

	RaycastHit hit1;
	PhysicsRay ray1(transform->position, mosterToPlayerDir, sqrtf(20.0f));

	m_jumptime += Time::FixedDeltaTime();

	if (m_jumptime > 3.f)
	{
		switch (attackType)
		{
		case Wendigo::AttackType::Jump:
			m_hasJump = Physics::Raycast(hit1, ray1, (1 << (PxU32)PhysicsLayers::Player) | (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::All, m_body);
			break;
		case Wendigo::AttackType::Swing:
			//m_hasJump = Physics::Raycast(hit1, ray1, (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::All, m_body);
			break;
		}
		m_jumptime = 0.f;
		m_jump = true;
	}

	if (m_jump)
	{
		m_jumpY = transform->position.y;
		m_jump = false;
	}

	if (!m_hasJump)
	{
		m_collider->friction = 0.0f;

	}
	else if (m_hasJump)
	{
		m_collider->friction = 1.0f;
	}
}

void Wendigo::SetAction(ActionType type)
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
	case ActionType::Swing:
	{
		m_attackCount = 2;
		attackType = AttackType::Swing;
		m_animator->PlaySwing();
	}
	case ActionType::Jump:
	{
		m_attackCount = 2;
		attackType = AttackType::Jump;
	}
	break;
	default:
		break;
	}
}

void Wendigo::AttackToPlayer()
{
}

void Wendigo::Attack()
{
	if (m_attackCount > 0)
	{
		--m_attackCount;

	
	}
}
