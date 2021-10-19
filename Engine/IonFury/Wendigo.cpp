#include "stdafx.h"
#include "Wendigo.h"
#include "WendigoSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"


void Wendigo::Awake()
{
	Monster::Awake();

	m_hp = 5;
	m_moveSpeed = 5.0f;

	m_body->mass = 3.f;
	m_body->interpolate = Interpolate::Extrapolate;


	m_rendererObj->transform->scale = Vec3::one() * 8.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -1.7f, 0);

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

	//JumpCheck();
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

	AttackType attackType = (AttackType)(rand() % unsigned int(AttackType::Max));


	if (!m_attacking && (m_breakTime <= 0))
	{
		actionType = (ActionType)(rand() % unsigned int(ActionType::Max));
		SetAction(actionType, attackType);
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
		renderer->transform->position = Vec3(transform->position.x, transform->position.y - 0.25f, transform->position.z);
	}

	m_capsuleCollider = colliderObj->AddComponent<CapsuleCollider>();

	return m_capsuleCollider;
}

void Wendigo::OnDamage(DamageParameters& params)
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
	if (m_hasJump)		// มกวม
	{
		if (m_attacking)
		{
			m_attackCount = 1;
			m_attacking = false;
		}
		Vec3 playerPos = Player::GetInstance()->transform->position;
		Vec3 monsterPos = transform->position;

		Vec3 forward = playerPos - monsterPos;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

		Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

		Vec3 velocity = Quat::AxisAngle(right, -65) * forward * m_moveSpeed;

		transform->position += velocity * 0.03f;

		m_animator->PlayAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Jump);
		//m_animator->SetDefaultAnimation(m_animator->GetAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Jump), true);

		if (transform->position.y > m_jumpY + 2.f)
		{
			m_attacking = true;
			m_hasJump = false;
			m_animator->PlayWalk();
			//m_animator->SetDefaultAnimation(m_animator->GetWalk(), true);
		}
	}
}

void Wendigo::JumpCheck()
{

	const Vec3& wendigoPos = transform->position;

	Vec3 forward = m_targetCoord - wendigoPos;
	forward.y = 0;
	forward.Normalize();

	transform->forward = forward;

	PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
	RaycastHit hit1;

	m_jumptime += Time::FixedDeltaTime();

	if (m_jumptime > 3.f)
	{
		if (Physics::Raycast(hit1, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::Collider, m_body))
		{
			m_hasJump = true;
		}

		m_jumptime = 0.f;
		m_jump = true;
	}

	if (m_jump)
	{
		m_jumpY = transform->position.y;
		m_jump = false;
	}

	//if (!m_hasJump)
	//{
	//	m_collider->friction = 0.0f;

	//}
	//else if (m_hasJump)
	//{
	//	m_collider->friction = 1.0f;
	//}
}

void Wendigo::SetAction(ActionType type, AttackType attacktype)
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
		//m_animator->SetDefaultAnimation(m_animator->GetAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Swing), true);
	//	m_animator->PlayAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Swing);
	}
	case ActionType::Jump:
	{

		//Jump();
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
}
