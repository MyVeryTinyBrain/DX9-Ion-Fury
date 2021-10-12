#include "stdafx.h"
#include "Drone.h"
#include "DroneSpriteAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"

void Drone::Awake()
{
	Monster::Awake();

	m_hp = 5;
	m_moveSpeed = 4.0f;

	m_body->mass = 1.f;
	m_body->interpolate = true;
	m_body->useGravity = false;

	m_rendererObj->transform->scale = Vec3::one() * 4.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -1, 0);

	m_animator = m_rendererChildObj->AddComponent<DroneSpriteAnimator>();
	
}

void Drone::FixedUpdate()
{
	Monster::FixedUpdate();

	Moving();

	//m_animator->SetAngle(AngleToPlayerWithSign());

	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Drone::Update()
{
	Monster::Update();

	//if (m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
	//	m_animator->PlayMove();
	//else
	//	m_animator->PlayIdle();

}

void Drone::OnDestroy()
{
	Monster::OnDestroy();
}

Collider* Drone::InitializeCollider(GameObject* colliderObj)
{
	return colliderObj->AddComponent<SphereCollider>();
}

void Drone::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
}

void Drone::OnDead(bool& dead, MonsterDamageType damageType)
{
}

void Drone::Moving()
{
	if (!m_hasTargetCoord)
		return;


	Vec3 dronePos = transform->position;
	Vec3 forward = m_targetCoord - dronePos;
	forward.y = dronePos.y;
	forward.Normalize();
	transform->forward = forward;
	transform->up = Vec3(0, 1, 0);
	transform->right = Vec3::Cross(transform->up, transform->forward);
	transform->right.Normalize();

	m_deltatime += Time::FixedDeltaTime();

	if (!m_animator->IsPlayingShoot() | !m_animator->IsPlayingMoveShoot())
	{
		m_moveSpeed = 4.0f;

		if (m_deltatime < 3.f)
		{
			transform->position += transform->right * m_moveSpeed * Time::FixedDeltaTime();
			m_animator->PlayMove();
			m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.0f);
		}
		else
		{
			transform->position += transform->right * m_moveSpeed * -Time::FixedDeltaTime();
			m_animator->PlayMove();
			m_animator->GetRenderer()->userMesh->uvScale = Vec2(-1.f, 1.0f);
			if (m_deltatime > 6.f)
			{
				m_deltatime = 0.f;
			}
		}
	}
	Vec3 xzdronePos = Vec3(dronePos.x, 0.f, dronePos.z);
	//float distance = Vec3::Distance(dronePos, m_targetCoord);

	PhysicsRay ray(xzdronePos, forward.normalized(), sqrtf(5.0f));
	RaycastHit hit;

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::Collider, m_body))
	{
		m_moveSpeed = 0.f;
		m_animator->PlayMoveShoot();
	}
}

void Drone::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;
}

void Drone::Attack()
{
	if (m_animator->IsPlayingShoot() | m_animator->IsPlayingMoveShoot())
	{
		return;
	}
	if (m_attackCount > 0)
	{
		--m_attackCount;
		m_animator->PlayShoot();

		// 플레이어를 바라봅니다.
		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;
	}
}
