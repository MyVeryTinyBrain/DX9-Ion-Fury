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
	//FindTarget();
	
	Moving(MovingType::Trace);
	
	
	Attack();


	m_animator->SetAngle(AngleToPlayerWithSign());


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

void Drone::Moving(MovingType type)
{
	if (!m_hasTargetCoord)
		return;

	Vec3 dronePos = transform->position;

	Vec3 forward = Player::GetInstance()->transform->position - dronePos;
	forward.y = dronePos.y;
	forward.Normalize();
	transform->forward = forward;

	transform->up = Vec3(0, 1, 0);
	transform->right = Vec3::Cross(transform->up, transform->forward);
	transform->right.Normalize();

	m_deltatime += Time::DeltaTime();


	switch (type)
	{
	case Drone::MovingType::Idle:
		break;
	case Drone::MovingType::Trace:
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
		//m_animator->PlayIdle();
	}
	break;
	case Drone::MovingType::leftRight:
	{
		if (m_deltatime < 3.f)
		{
			transform->position += transform->right * m_moveSpeed * Time::DeltaTime();
			m_animator->PlayMove();
			m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.0f);
		}
		else
		{
			transform->position += transform->right * m_moveSpeed * -Time::DeltaTime();
			m_animator->PlayMove();
			m_animator->GetRenderer()->userMesh->uvScale = Vec2(-1.f, 1.0f);
			if (m_deltatime > 6.f)
			{
				m_deltatime = 0.f;
			}
		}
	}
	break;
	case Drone::MovingType::Attack:
	{

	}
	break;
	}

	Vec3 acceleration = forward * m_moveSpeed;
	Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(25.f));
	velocity.y = m_body->velocity.y;
	m_body->velocity = velocity;


	//m_beforeCoord = transform->position;
	//m_beforeCoord.y = -1;
	//Vec3 dronePos = transform->position;
	//Vec3 forward = Player::GetInstance()->transform->position - dronePos;
	//forward.y = dronePos.y;
	//forward.Normalize();
	//transform->forward = forward;
	//transform->up = Vec3(0, 1, 0);
	//transform->right = Vec3::Cross(transform->up, transform->forward);
	//transform->right.Normalize();
	//m_deltatime += Time::DeltaTime();
	//if (!m_animator->IsPlayingShoot() | !m_animator->IsPlayingMoveShoot())
	//{
	//	m_moveSpeed = 4.0f;
	//	if (m_deltatime < 3.f)
	//	{
	//		transform->position += transform->right * m_moveSpeed * Time::DeltaTime();
	//		m_animator->PlayMove();
	//		m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.0f);
	//	}
	//	else
	//	{
	//		transform->position += transform->right * m_moveSpeed * -Time::DeltaTime();
	//		m_animator->PlayMove();
	//		m_animator->GetRenderer()->userMesh->uvScale = Vec2(-1.f, 1.0f);
	//		if (m_deltatime > 6.f)
	//		{
	//			m_deltatime = 0.f;
	//		}
	//	}
	//}

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

		
		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;
	}
}

void Drone::FindTarget()
{
	Vec3 dronePos = transform->position;
	Vec3 forward = m_targetCoord - dronePos;
	forward.y = dronePos.y;
	forward.Normalize();
	transform->forward = forward;

	Vec3 xzdronePos = Vec3(dronePos.x, dronePos.y, dronePos.z);
	//float distance = Vec3::Distance(dronePos, m_targetCoord);

	PhysicsRay ray(xzdronePos, forward.normalized(), sqrtf(5.0f));
	RaycastHit hit;

	if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::Collider, m_body))
	{
		m_attackCount = 1;

		
	}

}
