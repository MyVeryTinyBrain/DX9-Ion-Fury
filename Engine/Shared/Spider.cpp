#include "shared_stdafx.h"
#include "Spider.h"
#include "SpiderSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "Web.h"
#include "BloodEffect.h"

void Spider::Awake()
{
	Monster::Awake();

	m_hp = 10;
	m_moveSpeed = 2.0f;

	m_body->mass = 0.5f;
	m_body->interpolate = Interpolate::Extrapolate;


	m_rendererObj->transform->scale = Vec3::one() * 3.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -0.75f, 0);

	m_renderer = CreateRenderer();

	m_animator = m_renderer->gameObject->AddComponent<SpiderSpriteAnimator>();

}

void Spider::FixedUpdate()
{
	Monster::FixedUpdate();

	m_animator->SetAngle(AngleToPlayerWithSign());

#ifdef _AFX
	return;
#endif

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

void Spider::Update()
{
	Monster::Update();

#ifdef _AFX
	return;
#endif

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
		jumpingtype = (JumpType)(rand() % unsigned int(JumpType::MAX));
		m_PatternTime = 0.f;
	}
}

void Spider::OnDestroy()
{
	Monster::OnDestroy();

#ifdef _AFX
	return;
#endif
}

Collider* Spider::InitializeCollider(GameObject* colliderObj)
{

	//{
	//	auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);

	//}
	m_sphereCollider = colliderObj->AddComponent<SphereCollider>();
	m_sphereCollider->transform->localScale = Vec3::one() * 1.25f;


	return m_sphereCollider;
}

void Spider::OnDamage(DamageParameters& params)
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
		m_animator->SetDefaultAnimation(m_animator->GetDamage(), true);
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

	params.force = Vec3::zero();
}

void Spider::OnDead(bool& dead, DamageParameters& params)
{
	m_hasTargetCoord = false;
	m_attackCount = 0;
	
	int dieIndex = rand() % (int)SpiderSpriteAnimator::DIE_SPIDER::MAX;


	if (params.damageType == MonsterDamageType::Explosion)
	{
		dieIndex = (int)MonsterDamageType::Explosion;
	}

	m_animator->PlayDie((SpiderSpriteAnimator::DIE_SPIDER)dieIndex);
}

void Spider::MoveToTarget()
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
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}


}

void Spider::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;
}

void Spider::Attack()
{
	if (m_attackCount > 0)
	{
		--m_attackCount;

		// 거미줄 
		auto obj = CreateGameObject();
		obj->transform->position = transform->position + transform->forward;// *2.f;
		obj->transform->forward = transform->forward;
		obj->AddComponent<Web>();

	}
}

void Spider::JumpCheck()
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
		switch (jumpingtype)
		{
		case Spider::JumpType::BASIC:
			m_hasJump = Physics::Raycast(hit1, ray1, (1 << (PxU32)PhysicsLayers::Player) | (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::All, m_body);
			break;
		case Spider::JumpType::WEB:
			m_hasJump = Physics::Raycast(hit1, ray1, (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::All, m_body);
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

void Spider::Jump()
{

	if (m_hasJump)		// 점프
	{
		if (m_attack && jumpingtype == JumpType::WEB)
		{
			m_attackCount = 1;
			m_attack = false;
		}
		Vec3 playerPos = Player::GetInstance()->transform->position;
		Vec3 monsterPos = transform->position;

		Vec3 forward = playerPos - monsterPos;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

		Vec3 right = Vec3(transform->right.x, 0, transform->right.z);

		Vec3 velocity = Quat::AxisAngle(right, -65) * forward * m_moveSpeed;

		transform->position += velocity * Time::DeltaTime() * 2.5f;

		m_animator->SetDefaultAnimation(m_animator->GetJump(), true);

		AttackToPlayer();

		if (transform->position.y > m_jumpY + 1.f)
		{
			if(jumpingtype == JumpType::WEB)
				m_attack = true;
			m_hasJump = false;
			m_animator->SetDefaultAnimation(m_animator->GetWalk(), true);
		}
	}
}

void Spider::AttackToPlayer()
{
	Vec3 mosterToPlayerDir = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayerDir.y = 0;
	mosterToPlayerDir.Normalize();

	RaycastHit hit;
	PhysicsRay ray(transform->position, mosterToPlayerDir, sqrtf(0.1f));

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Player) | (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::All, m_body))
	{
		if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{
			Player::GetInstance()->TakeDamage(1);
		}
	}
}

