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

	// 목표 지점이 없는 경우에 목표 지점을 랜덤하게 재설정합니다.
	if (!m_hasTargetCoord)
	{

		float randomRadian = (rand() % 360) * Deg2Rad;
		float randomDistance = (rand() % 15) + 2.1f + 0.1f;
		Vec3 targetCoord = Vec3(cosf(randomRadian), 0, sinf(randomRadian) * randomDistance);
		//Vec3 targetCoord = Player::GetInstance()->transform->position;
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

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain | (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
		{
			float angle = Vec3::Angle(hit.normal, Vec3::up());
			m_hasJump = true;

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

		if (m_hasJump)		// 점프
		{
			Vec3 velocity = m_body->velocity;
			velocity.y = m_jumpSpeed;
			m_body->velocity = velocity;

			transform->position += Vec3::up() * 0.05f;
			m_body->ApplyBodyTransformFromGameObject();
			m_hasJump = false;
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
