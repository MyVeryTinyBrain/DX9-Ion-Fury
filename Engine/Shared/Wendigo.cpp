#include "shared_stdafx.h"
#include "Wendigo.h"
#include "WendigoSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"

void Wendigo::Awake()
{

	Monster::Awake();

	gameObject->transform->scale = Vec3::one() * 1.5f;

	m_hp = 50.0f;
	m_moveSpeed = 3.0f;

	m_body->mass = 10.0f;
	m_body->interpolate = Interpolate::Extrapolate;
	m_body->sleepThresholder = 2.0f;

	m_rendererObj->transform->localScale = Vec3::one() * 6.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -1.f, 0);

	m_renderer = CreateRenderer();
	m_animator = m_renderer->gameObject->AddComponent<WendigoSpriteAnimator>();
	m_animator->OnPlayedJump += Function<void()>(this, &Wendigo::OnPlayedJump);
	m_animator->OnPlayedSwing += Function<void()>(this, &Wendigo::OnPlayedSwing);
	m_animator->OnPlayedAttack += Function<void()>(this, &Wendigo::OnPlayedAttack);
	m_animator->OnPlayedDie += Function<void()>(this, &Wendigo::OnPlayedDie);


	m_defaultEmissive = Color::white();

	SetBehavior(Behavior::Idle);
}

void Wendigo::FixedUpdate()
{
	Monster::FixedUpdate();

	if (Time::FixedTimeScale() == 0)
		return;

	//if (m_isDead)
	//{
	//	return;
	//}

	//MoveToTarget();

	//JumpCheck();
}

void Wendigo::Update()
{
	Monster::Update();

	float angleToPlayer = AngleToPlayerWithSign();

	m_animator->SetAngle(angleToPlayer);

	if (Time::TimeScale() == 0)
		return;

	if (isDead)
	{
		return;
	}

	BehaviorUpdate();


	//if (m_isDead)
	//{
	//	return;
	//}
	//if (m_isDead)
	//{
	//	if (m_body)
	//	{
	//		m_body->Destroy();
	//		m_collider->Destroy();
	//		m_body = nullptr;
	//		m_collider = nullptr;
	//	}
	//	return;
	//}

	////AttackType attackType = (AttackType)(rand() % unsigned int(AttackType::Max));


	//if (!m_attacking && (m_breakTime <= 0))
	//{
	//	actionType = (ActionType)(rand() % unsigned int(ActionType::Max));
	//	SetAction(actionType);
	//}

	//if (m_breakTime > 0 && m_animator->IsPlayingIdle())
	//{
	//	m_breakTime -= Time::DeltaTime();
	//}


	//if (m_animator->IsPlayingIdle() && m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
	//{
	//	m_animator->PlayWalk();
	//}
	//else if (m_animator->IsPlayingWalk() && m_body->velocity.magnitude() < m_moveSpeed * 0.5f)
	//{
	//	m_animator->PlayDefaultAnimation();
	//}

	//Attack();

	//Jump();

	//m_animator->SetAngle(AngleToPlayerWithSign());

}

void Wendigo::LateUpdate()
{
	Monster::LateUpdate();

	if (Time::TimeScale() == 0)
		return;
}

void Wendigo::OnDestroy()
{
	Monster::OnDestroy();

	m_animator->OnPlayedJump -= Function<void()>(this, &Wendigo::OnPlayedJump);
	m_animator->OnPlayedSwing -= Function<void()>(this, &Wendigo::OnPlayedSwing);
	m_animator->OnPlayedAttack -= Function<void()>(this, &Wendigo::OnPlayedAttack);

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
		//renderer->transform->scale = Vec3(2.f, 1.5f, 1.5f);
		//renderer->transform->position = Vec3(transform->position.x, transform->position.y - 0.5f, transform->position.z);
	}

	m_capsuleCollider = colliderObj->AddComponent<CapsuleCollider>();
	/*m_capsuleCollider->transform->scale = Vec3(2.f, 1.3f, 2.f);
	m_capsuleCollider->transform->position = Vec3(transform->position.x, transform->position.y - 0.8f, transform->position.z);*/


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
	Vec3 monsterToPlayer = playerPos - wndigoPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = monsterToPlayer;
}

void Wendigo::OnDead(bool& dead, DamageParameters& params)
{
	m_hasTargetCoord = false;
	m_attackCount = 0;
	m_breakTime = FLT_MAX;


	m_animator->PlayDie();

}

void Wendigo::OnPlayedJump()
{
	
}

void Wendigo::OnPlayedSwing()
{
	SetBehavior(Behavior::Swing);
}

void Wendigo::OnPlayedAttack()
{
}

void Wendigo::OnPlayedDie()
{
}

void Wendigo::SetBehavior(Behavior value)
{
	if (value == Behavior::None || value == Behavior::RandomMax)
	{
		return;
	}

	if (value == m_behavior)
	{
		return;
	}

	m_behavior = value;

	switch (m_behavior)
	{
	case Wendigo::Behavior::Idle:
		OnIdle();
		break;
	case Wendigo::Behavior::MoveToPlayer:
		OnMoveToPlayer();
		break;
	case Wendigo::Behavior::Jump:
		OnJump();
		break;
	case Wendigo::Behavior::Swing:
		OnSwing();
		break;
	//case Wendigo::Behavior::WalkToRandomCoord:
	//	OnWalkToRandomCoord();
	//	break;
	}

}

void Wendigo::BehaviorUpdate()
{
	switch (m_behavior)
	{
	case Wendigo::Behavior::Idle:
		Idle();
		break;
	case Wendigo::Behavior::MoveToPlayer:
		MoveToPlayer();
		break;
	case Wendigo::Behavior::Jump:
		Jump();
		break;
	case Wendigo::Behavior::Swing:
		Swing();
		break;
	//case Wendigo::Behavior::WalkToRandomCoord:
	//	WalkToRandomCoord();
	//	break;
	}
}

void Wendigo::OnIdle()
{
	m_idleAccumulate = 0.0f;

	m_animator->PlayIdle();
}

void Wendigo::Idle()
{
	m_idleAccumulate += Time::DeltaTime();

	if (m_idleAccumulate > 1.0f)
	{
		int iBehavior = (rand() % (int)Behavior::RandomMax);
		SetBehavior((Behavior)iBehavior);
		return;
	}
}

void Wendigo::OnMoveToPlayer()
{
	Vec3 target = Player::GetInstance()->transform->position;
	target.y = 0;

	Vec3 xzwendigoPos = transform->position;
	xzwendigoPos.y = 0;

	float distance = Vec3::Distance(xzwendigoPos,target);

	if (distance < 3.0f + 0.1f)
	{
		SetBehavior(Behavior::Swing);
		return;
	}

	Vec3 monsterToPlayer = target - xzwendigoPos;
	Vec3 dir = monsterToPlayer.normalized();

	transform->forward = dir;
	m_moveToPlayerAccumulate = 0;
}

void Wendigo::MoveToPlayer()
{
	Vec3 target = Player::GetInstance()->transform->position;
	target.y = 0;

	Vec3 xzwendigoPos = transform->position;
	xzwendigoPos.y = 0;

	float distance = Vec3::Distance(xzwendigoPos, target);

	Vec3 monsterToPlayer = target - xzwendigoPos;
	Vec3 dir = monsterToPlayer.normalized();

	if (m_body->velocity.magnitude() > m_moveSpeed * 0.5f)
	{
		m_animator->PlayWalk();
	}
	else
	{
		m_animator->PlayIdle();
	}

	if (distance < 3.0f)
	{
		SetBehavior(Behavior::Idle);
	}
	//else if (WallTest(dir))
	//{
	//	SetBehavior(Behavior::FlyToPlayer);
	//	return;
	//}
	else if (m_moveToPlayerAccumulate > 3.0f)
	{
		SetBehavior(Behavior::Swing);
	}
	else
	{
		Vec3 vel = dir * m_moveSpeed;
		vel = ToSlopeVelocity(vel, sqrtf(2.0f) * 1.5f);

		if (Abs(vel.y) < 0.1f)
		{
			m_body->velocity = Vec3(vel.x, m_body->velocity.y, vel.z);
		}
		else
		{
			m_body->velocity = vel;
		}

		transform->forward = dir;
	}

	m_moveToPlayerAccumulate += Time::DeltaTime();
}

void Wendigo::OnJump()
{
	//Vec3 target = Player::GetInstance()->transform->position;
	//target.y = 0;

	//Vec3 xzwendigoPos = transform->position;
	//xzwendigoPos.y = 0;

	//float distance = Vec3::Distance(xzwendigoPos, target);

	//if (distance < 5.f)
	//{
	//	m_animator->PlayJump();
	//}

	m_hasJump = true;

	m_animator->PlayJump();
}

void Wendigo::OnSwing()
{
	m_animator->PlaySwing();
}

void Wendigo::OnWalkToRandomCoord()
{
}

void Wendigo::Swing()
{
	m_animator->PlaySwing();

	Vec3 mosterToPlayerDir = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayerDir.y = 0;
	mosterToPlayerDir.Normalize();

	RaycastHit hit;
	PhysicsRay ray(transform->position, mosterToPlayerDir, sqrtf(0.1f));

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::All, m_body))
	{
		if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{
			Player::GetInstance()->TakeDamage(1);
		}
	}
}

void Wendigo::WalkToRandomCoord()
{
	float randomRadian = (rand() % 360) * Deg2Rad;
	float randomDistance = (rand() % 15) + 2.1f + 0.1f;
	Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
	SetTargetCoord(targetCoord);


}

void Wendigo::MoveToTarget()
{
	//if (!m_hasTargetCoord)
	//{
	//	return;
	//}

	//const Vec3& wendigoPos = transform->position;

	//Vec3 forward = m_targetCoord - wendigoPos;
	//forward.y = 0;
	//forward.Normalize();

	//transform->forward = forward;

	//Vec3 xzWendigoPos = Vec3(wendigoPos.x, 0, wendigoPos.z);

	//float distance = Vec3::Distance(xzWendigoPos, m_targetCoord);

	//if (distance > 2.1f)
	//{

	//	PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
	//	RaycastHit hit;

	//	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
	//	{
	//		float angle = Vec3::Angle(hit.normal, Vec3::up());

	//		if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain && angle > 85 && angle < 95)
	//		{
	//			m_hasTargetCoord = false;
	//			return;
	//		}
	//		else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
	//		{
	//			m_hasTargetCoord = false;
	//			return;
	//		}
	//	}

	//	Vec3 acceleration = forward * m_moveSpeed;
	//	Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
	//	velocity.y = m_body->velocity.y;
	//	m_body->velocity = velocity;

	//	if (Vec3::Distance(xzWendigoPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
	//	{
	//		m_hasTargetCoord = false;
	//		return;
	//	}
	//	m_beforeCoord = transform->position;
	//	m_beforeCoord.y = 0;
	//}
	//else
	//{
	//	m_hasTargetCoord = false;
	//}
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

		transform->position += velocity * Time::DeltaTime() * 2.5f;

		if (transform->position.y > m_jumpY + 1.f)
		{
			m_hasJump = false;
			m_animator->PlayWalk();
		}

	}
}

void Wendigo::JumpCheck()
{
//	PhysicsRay ray(transform->position, Vec3::down(), sqrtf(0.1f));
//	RaycastHit hit;
//
//	if (m_hasJump)
//	{
//		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider, m_body))
//		{
//
//			if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
//			{
//				//if (transform->position.y > m_jumpY + 2.f)
//				//{
//					m_hasJump = false;
//					//m_moveSpeed = 0.f;
//
////				}
//			}
//		}
//	}
}

void Wendigo::SetAction(ActionType type)
{
	//m_hasTargetCoord = false;
	//m_attackCount = 0;
	//m_breakTime = 0.35f;

	//switch (type)
	//{
	//case ActionType::Idle:
	//{

	//}
	//break;
	//case ActionType::WalkToRandomCoord:
	//{
	//	float randomRadian = (rand() % 360) * Deg2Rad;
	//	float randomDistance = (rand() % 15) + 2.1f + 0.1f;
	//	Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
	//	SetTargetCoord(targetCoord);
	//}
	//break;
	//case ActionType::WalkToPlayerDirection:
	//{
	//	const Vec3& monsterPos = transform->position;
	//	const Vec3& playerPos = Player::GetInstance()->transform->position;
	//	Vec3 relative = playerPos - monsterPos;
	//	float distance = Clamp(relative.magnitude(), 0, 8.0f);
	//	Vec3 direction = relative.normalized();
	//	SetTargetCoord(monsterPos + direction * distance);
	//}
	//break;
	//case ActionType::Swing:
	//{
	//	m_attackCount = 2;
	//	attackType = AttackType::Swing;
	//	m_animator->PlayAttack(WendigoSpriteAnimator::ATTACK_WENDIGO::Swing);
	//	m_attacking = true;
	//}
	//case ActionType::Jump:
	//{
	//	m_attackCount = 2;
	//	attackType = AttackType::Jump;

	//	m_hasJump = true;
	//	m_jump = true;
	//	m_attacking = true;
	//}
	//break;
	//default:
	//	break;
	//}

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

	//if (m_attackCount > 0)
	//{
	//	switch (attackType)
	//	{
	//	case Wendigo::AttackType::Swing:
	//	{
	//		--m_attackCount;

	//	}
	//	break;
	//	case Wendigo::AttackType::Jump:
	//	{
	//		--m_attackCount;


	//	}
	//	break;
	//	}


	//	Vec3 forward = Player::GetInstance()->transform->position - transform->position;
	//	forward.y = 0;
	//	forward.Normalize();
	//	transform->forward = forward;

	//}
	//else
	//	m_attacking = false;
}
