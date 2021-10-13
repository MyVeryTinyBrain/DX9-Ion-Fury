#include "stdafx.h"
#include "Spider.h"
#include "SpiderSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"

void Spider::Awake()
{
	Monster::Awake();

	m_hp = 5;
	m_moveSpeed = 2.0f;

	m_body->mass = 0.5f;
	m_body->interpolate = true;

	m_rendererObj->transform->scale = Vec3::one() * 3.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -0.5, 0);

	m_animator = m_rendererChildObj->AddComponent<SpiderSpriteAnimator>();

}

void Spider::FixedUpdate()
{
	Monster::FixedUpdate();

	MoveToTarget();

	m_animator->SetAngle(AngleToPlayerWithSign());

	
	JumpCheck();



	// 목표 지점이 없는 경우에 목표 지점을 랜덤하게 재설정합니다.
	if (!m_hasTargetCoord )
	{
		float randomRadian = (rand() % 360) * Deg2Rad;
		float randomDistance = (rand() % 15) + 2.1f + 0.1f;
		//Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Spider::Update()
{
	Monster::Update();


	Jump();

	if (m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
		m_animator->PlayWalk();
	else
		m_animator->PlayIdle();

}

void Spider::OnDestroy()
{
	Monster::OnDestroy();
}

Collider* Spider::InitializeCollider(GameObject* colliderObj)
{
	return colliderObj->AddComponent<SphereCollider>();
}

void Spider::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
	Vec3 bound;

	switch (damageType)
	{
	case MonsterDamageType::Bullet:
		m_animator->PlayDie(SpiderSpriteAnimator::DIE_SPIDER::DIE_GENERIC);
		break;
	case MonsterDamageType::Explosion:
		m_animator->PlayDie(SpiderSpriteAnimator::DIE_SPIDER::DIE_HEADSHOT);

		//bound = transform->forward;
		//bound.y = 0;
		//bound.Normalize();

		//transform->position += bound * m_moveSpeed * -Time::DeltaTime();
		break;
	case MonsterDamageType::Zizizik:
		m_animator->PlayDamage();
		break;
	}


}

void Spider::OnDead(bool& dead, MonsterDamageType damageType)
{
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
		
		Vec3 velocity= forward * m_moveSpeed;
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

	}
}

void Spider::JumpCheck()
{

	Vec3 mosterToPlayerDir = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayerDir.y = 0;
	mosterToPlayerDir.Normalize();

	RaycastHit hit1;
	PhysicsRay ray1(transform->position, mosterToPlayerDir, sqrtf(20.0f));
	
	m_jumptime += Time::FixedDeltaTime();

	if (m_jumptime > 3.f)
	{
		m_hasJump = Physics::Raycast(hit1, ray1, (1 << (PxU32)PhysicsLayers::Player) /*| (1 << (PxU32)PhysicsLayers::Terrain)*/, PhysicsQueryType::All, m_body);
		m_jumptime = 0.f;
		m_jump = true;
	}

	if (m_jump)
	{
		m_jumpY = transform->position.y;
		m_jump = false;
	}
	if (m_hasJump)
	{
		//if (hit1.collider->layerIndex == (PxU32)PhysicsLayers::Player)
		//{
		//	m_attackCount = 1;

		//	m_jumpCount = 1;

		//	m_animator->PlayJump();
		//}
	}
	if (!m_hasJump)
	{
		m_collider->friction = 0.0f;
	
	}
	else if (m_hasJump & (m_jumpCount > 0))
	{
		m_collider->friction = 1.0f;
	}
}

void Spider::Jump()
{

	if (m_hasJump)		// 점프
	{
		Vec3 playerPos = Player::GetInstance()->transform->position;
		Vec3 monsterPos = transform->position;
		
		Vec3 forward = playerPos - monsterPos;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

		Vec3 velocity = Quat::AxisAngle(transform->right, -45) * forward;
		m_body->velocity = velocity;


		m_animator->SetAngle(AngleToPlayerWithSign());

		transform->position += Vec3::up() * 0.05f;

		if (transform->position.y > m_jumpY + 3.f)
		{
			m_hasJump = false;
		}

		//{
		//	web = CreateGameObject();
		//	web->transform->position = Vec3(transform->position.x, transform->position.y, transform->position.z);
		//	web->transform->scale = Vec3::one() * 2.0f;

		//	auto renderer = web->AddComponent<UserMeshRenderer>();
		//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
		//	renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/spider/Web_01.png"));
		//	webBody = web->AddComponent<Rigidbody>();
		//	webBody->isKinematic = true;
		//	auto collider = web->AddComponent<BoxCollider>();
		//	renderer->material = m_material;

		//	web->transform->forward = -transform->forward;

		//	Vec3 webPos = web->transform->position;
		//	Vec3 webforward = (monsterPos + web->transform->forward * 2.f)  - monsterPos;
		//	webforward.Normalize();


		//	web->transform->position += forward * 0.03f;
		//}


	}

}
