#include "shared_stdafx.h"
#include "Wendigo.h"
#include "WendigoSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"
#include "WarmechHit.h"

void Wendigo::Awake()
{
	Monster::Awake();

	m_hp = 50;
	m_moveSpeed = 3.0f;

	m_body->mass = 5.f;
	m_body->interpolate = Interpolate::Extrapolate;


	m_rendererObj->transform->scale = Vec3::one() * 8.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -1.3f, 0);

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

	//TerrainCheck();

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

	if (m_PatternTime > 1.f)
	{
		actionType = (ActionType)(rand() % unsigned int(ActionType::Max));
		SetAction(actionType);
		m_PatternTime = 0.f;
	}

	if (m_playerHit)
	{
		Player::GetInstance()->TakeDamage(1);
		transform->position += Player::GetInstance()->transform->forward * Time::DeltaTime() * 2.f;
		m_playerHit = false;
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
	m_capsuleCollider->transform->scale = Vec3::one() * 1.3f;

	return m_capsuleCollider;
}

void Wendigo::OnDamage(DamageParameters& params)
{
	m_hasTargetCoord = false;

	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
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
	params.force = Vec3::zero();

	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& wendigoPos = transform->position;
	Vec3 forward = playerPos - wendigoPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
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

	const Vec3& wendigoPos = Vec3(transform->position.x, transform->position.y - 0.5f, transform->position.z);
	Vec3 forward = m_targetCoord - wendigoPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;

	Vec3 xzWendigoPos = Vec3(wendigoPos.x, 0, wendigoPos.z);
	float distance = Vec3::Distance(xzWendigoPos, m_targetCoord);

	if (distance > 2.1f)
	{
		PhysicsRay ray(wendigoPos, forward.normalized(), sqrtf(1.0f));
		RaycastHit hit;

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
		{
			float angle = Vec3::Angle(hit.normal, Vec3::up());

			if (hit.collider->layerIndex == (PxU32)PhysicsLayers::Terrain && angle > 85 && angle < 95)
			{
				m_hasTargetCoord = false;
				m_hasJump = true;

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
		//Vec3 targetCoord = Player::GetInstance()->transform->position;
		//SetTargetCoord(targetCoord);
	}

}

void Wendigo::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;

	Vec3 forward = xzCoord - transform->position;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
}

void Wendigo::Jump()
{
	if (m_animator->IsPlayingWalk())
		return;

	if (m_hasJump)		// มกวม
	{

		Vec3 playerPos = Player::GetInstance()->transform->position;
		Vec3 monsterPos = transform->position;


		m_forward = playerPos - monsterPos;
		m_forward.y = 0;
		m_forward.Normalize();
		transform->forward = m_forward;

		Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

		m_animator->PlayJump();

		Vec3 velocity = Quat::AxisAngle(right, -65.f) * m_forward * m_moveSpeed;


		transform->position += velocity * Time::DeltaTime() * 2.5f;

		//m_animator->SetDefaultAnimation(m_animator->GetAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Jump), true);

		AttackToPlayer();

	

		if (transform->position.y > m_jumpY + 1.0f)
		{
			m_hasJump = false;
			//m_animator->PlayWalk();
			
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
	PhysicsRay ray1(transform->position + Vec3::down(), mosterToPlayerDir, sqrtf(20.0f));

	m_jumptime += Time::FixedDeltaTime();

	if (m_jumptime > 0.5f)
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
		m_animator->IsPlayingJump();
		m_collider->friction = 1.0f;
	}
}

void Wendigo::TerrainCheck()
{

	//if (m_animator->IsPlayingJump())
	//{
	//	return;
	//}

	Vec3 mosterToPlayerDir = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayerDir.y = 0;
	mosterToPlayerDir.Normalize();

	RaycastHit hit1;
	PhysicsRay ray1(transform->position + Vec3::down(), mosterToPlayerDir, sqrtf(2.0f));


	if (Physics::Raycast(hit1, ray1, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::All, m_body))
	{
		m_hasJump = true;
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
		actionType = (ActionType)(rand() % unsigned int(ActionType::Max));
	}
	break;
	case ActionType::WalkToRandomCoord:
	{
		//float randomRadian = (rand() % 360) * Deg2Rad;
		//float randomDistance = (rand() % 15) + 2.1f + 0.1f;
		//Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
		//SetTargetCoord(targetCoord);
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
		m_animator->IsPlayingJump();
		attackType = AttackType::Jump;
	}
	break;
	}
}

void Wendigo::AttackToPlayer()
{
	if ((!m_animator->IsPlayingAttack()) | m_playerHit)
	{
		return;
	}

	Vec3 mosterToPlayerDir = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayerDir.y = 0;
	mosterToPlayerDir.Normalize();

	RaycastHit hit;
	PhysicsRay ray(transform->position + Vec3::down(), mosterToPlayerDir, sqrtf(0.33f));

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Player) | (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::All, m_body))
	{
		if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{
			m_playerHit = true;
	
		}
	}
}

void Wendigo::Attack()
{

}
