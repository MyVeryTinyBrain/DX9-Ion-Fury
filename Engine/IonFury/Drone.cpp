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

	m_animator->SetAngle(AngleToPlayerWithSign());

	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Drone::Update()
{
	Monster::Update();

	if (m_body->velocity.magnitude() >= m_moveSpeed * 0.5f)
		m_animator->PlayMove();
	else
		m_animator->PlayIdle();

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


	Vec3 forward = m_targetCoord - transform->position;
	forward.y = transform->position.y;
	forward.Normalize();
	transform->forward = forward;
	transform->up = Vec3(0, 1, 0);
	transform->right = Vec3::Cross(transform->up, transform->forward);
	transform->right.Normalize();

	m_deltatime += Time::FixedDeltaTime();


	if (m_deltatime < 3.f)
	{
		transform->position += transform->right * m_moveSpeed * Time::FixedDeltaTime();
		
	}
	else
	{
		transform->position += transform->right * -m_moveSpeed * Time::FixedDeltaTime();
		if (m_deltatime > 6.f)
		{
			m_deltatime = 0.f;
		}
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
}
