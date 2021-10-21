#include "shared_stdafx.h"
#include "Wendigo.h"
#include "WendigoSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"

void Wendigo::Awake()
{
	Monster::Awake();

	m_hp = 50;
	m_moveSpeed = 3.0f;

	m_body->mass = 5.f;
	m_body->interpolate = Interpolate::Extrapolate;


	m_rendererObj->transform->scale = Vec3::one() * 8.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -2.f, 0);

	m_renderer = CreateRenderer();

	m_animator = m_renderer->gameObject->AddComponent<WendigoSpriteAnimator>();
}

void Wendigo::FixedUpdate()
{
	Monster::FixedUpdate();

	if (m_isDead)
	{
		return;
	}

	MoveToTarget();

	JumpCheck();
}

void Wendigo::Update()
{
	Monster::Update();

	if (m_isDead)
	{
		return;
	}
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

	//AttackType attackType = (AttackType)(rand() % unsigned int(AttackType::Max));


	if (!m_attacking && (m_breakTime <= 0))
	{
		actionType = (ActionType)(rand() % unsigned int(ActionType::Max));
		SetAction(actionType);
	}

	if (m_breakTime > 0 && m_animator->IsPlayingIdle())
	{
		m_breakTime -= Time::DeltaTime();
	}


	if (m_animator->IsPlayingIdle() && m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
	{
		m_animator->PlayWalk();
	}
	else if (m_animator->IsPlayingWalk() && m_body->velocity.magnitude() < m_moveSpeed * 0.5f)
	{
		m_animator->PlayDefaultAnimation();
	}

	Attack();

	Jump();

	m_animator->SetAngle(AngleToPlayerWithSign());

}

void Wendigo::OnDestroy()
{
	Monster::OnDestroy();

}

Collider* Wendigo::InitializeCollider(GameObject* colliderObj)
{
	{
		auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
		renderer->transform->scale = Vec3(2.f, 1.5f, 1.5f);
		renderer->transform->position = Vec3(transform->position.x, transform->position.y - 0.5f, transform->position.z);
	}

	m_capsuleCollider = colliderObj->AddComponent<CapsuleCollider>();

	return m_capsuleCollider;
}

void Wendigo::OnDamage(DamageParameters& params)
{
	m_hasTargetCoord = false;
	//m_attackCount = 5;
	//m_breakTime = 0.35f;

	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
	{
		{
			GameObject* bloodEffectObj = CreateGameObject();
			bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
			bloodEffectObj->AddComponent<BloodEffect>();
		}

	}

	params.force = Vec3::zero();

	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& wndigoPos = transform->position;
	Vec3 forward = playerPos - wndigoPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
}

void Wendigo::OnDead(bool& dead, DamageParameters& params)
{
	m_hasTargetCoord = false;
	m_attackCount = 0;
	m_breakTime = FLT_MAX;


	m_animator->PlayDie();

}

void Wendigo::MoveToTarget()
{
	if (!m_hasTargetCoord)
	{
		return;
	}

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

	if (m_jump)
	{
		m_jumpY = transform->position.y;
		m_jump = false;
	}

	if (m_hasJump)		// มกวม
	{
		m_animator->PlayAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Jump);

		Vec3 playerPos = Player::GetInstance()->transform->position;
		Vec3 missilePos = transform->position;


		if (m_initialdir)
		{
			forward = playerPos - missilePos;
			forward.Normalize();
			transform->forward = forward;
			m_initialdir = false;
		}

		Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

		Vec3 velocity = Quat::AxisAngle(right, -22.5f) * forward * m_moveSpeed;

		transform->position += velocity * 0.03f;


	}
	else if(attackType == AttackType::Jump && !m_hasJump)
	{
		m_animator->PlayWalk();
	}
}

void Wendigo::JumpCheck()
{
	PhysicsRay ray(transform->position, Vec3::down(), sqrtf(0.1f));
	RaycastHit hit;

	if (m_hasJump)
	{
		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider, m_body))
		{

			if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
			{
				//if (transform->position.y > m_jumpY + 2.f)
				//{
					m_hasJump = false;
					//m_moveSpeed = 0.f;

//				}
			}
		}
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
		m_animator->PlayAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Swing);
		m_attacking = true;
	}
	case ActionType::Jump:
	{
		m_attackCount = 2;
		attackType = AttackType::Jump;

		m_hasJump = true;
		m_jump = true;
		m_attacking = true;
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
	//if (m_animator->IsPlayingAttack())
	//{
	//	return;
	//}

	if (m_attackCount > 0)
	{
		switch (attackType)
		{
		case Wendigo::AttackType::Swing:
		{
			--m_attackCount;

		}
		break;
		case Wendigo::AttackType::Jump:
		{
			--m_attackCount;


		}
		break;
		}


		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

	}
	else
		m_attacking = false;
}
