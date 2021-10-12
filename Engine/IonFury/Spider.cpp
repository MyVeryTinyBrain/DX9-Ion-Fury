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

	// ��ǥ ������ ���� ��쿡 ��ǥ ������ �����ϰ� �缳���մϴ�.
	if (!m_hasTargetCoord)
	{
		float randomRadian = (rand() % 360) * Deg2Rad;
		float randomDistance = (rand() % 15) + 2.1f + 0.1f;
		Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian)) * randomDistance;
		SetTargetCoord(targetCoord);
	}
}

void Spider::Update()
{
	Monster::Update();

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
		
		bound = transform->forward;
		bound.y = 0;
		bound.Normalize();

		transform->position += bound * m_moveSpeed * -Time::DeltaTime();
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


		Vec3 target = Player::GetInstance()->transform->position - spiderPos;
		target.y = 0;
		target.Normalize();

		RaycastHit hit1;
		PhysicsRay ray1(transform->position, target, sqrtf(5.0f));

		m_hasJump = Physics::Raycast(hit1, ray1, (1 << (PxU32)PhysicsLayers::Player) | (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::All, m_body);

		//m_hasJump = Physics::RaycastTest(ray1, (1 << (PxU32)PhysicsLayers::Player) | (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::All, m_body);

		if (m_hasJump)		// ����
		{
			Vec3 velocity = m_body->velocity;
			velocity.y = m_jumpSpeed;
			m_body->velocity = velocity;

			transform->position += Vec3::up() * 0.05f;
			m_body->ApplyBodyTransformFromGameObject();

			m_hasJump = false;

			transform->forward = target;
			m_animator->PlayJump();

			//if (hit.collider->layerIndex == (PxU32)PhysicsLayers::Player)
			//{
			//	m_attackCount = 1;
			//}

		}
		else
		{
			Vec3 acceleration = forward * m_moveSpeed;
			Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
			velocity.y = m_body->velocity.y;
			m_body->velocity = velocity;
		}

		if (!m_hasJump)
		{
			m_collider->friction = 0.0f;
		}
		else
		{
			m_collider->friction = 1.0f;
		}

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
		// �Ź��� 
	}
}