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


	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Drone::Update()
{
	Monster::Update();


	//Moving(MovingType::Attack);
	if (m_breakTime <= 0)
	{
		MovingType movingtype = (MovingType)(rand() % unsigned int(MovingType::Max));
		Moving(movingtype);
	}

	if (m_breakTime > 0 )
	{
		m_breakTime -= Time::DeltaTime();
	}

	Attack();

	m_animator->SetAngle(AngleToPlayerWithSign());

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
	m_hasTargetCoord = false;
	m_attackCount = 0;
	m_breakTime = 0.35f;

	Vec3 dronePos = transform->position;

	Vec3 forward = Player::GetInstance()->transform->position - dronePos;
	forward.Normalize();
	transform->forward = forward;

	switch (type)
	{
	case Drone::MovingType::Idle:
		break;
	case Drone::MovingType::Trace:
	{
		Vec3 xzdronePos = Vec3(dronePos.x, 0, dronePos.z);
		float distance = Vec3::Distance(xzdronePos, Player::GetInstance()->transform->position);

		if (distance > 8.f)
			m_distance = true;
		else
			m_distance = false;

		if (m_distance)
		{
			m_animator->PlayIdle();
			Vec3 targetCoord = Player::GetInstance()->transform->position;
			SetTargetCoord(targetCoord);

			Vec3 velocity = forward * m_moveSpeed;
			velocity.y = 0;
			m_body->velocity = velocity;
		}

		m_deltatime += Time::DeltaTime();

		if (m_deltatime < 1.5f)
		{
			transform->position += transform->up * m_moveSpeed * Time::DeltaTime();
		}
		else
		{
			transform->position += transform->up * m_moveSpeed * -Time::DeltaTime();
			
			if (m_deltatime > 3.f)
			{
				m_deltatime = 0.f;
			}
		}
	}
	break;
	case Drone::MovingType::leftRight:
	{
		transform->up = Vec3(0, 1, 0);
		transform->right = Vec3::Cross(transform->up, transform->forward);
		transform->right.Normalize();

		m_deltatime += Time::DeltaTime();

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
		m_attackCount = 5;
	}
	break;
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


		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;
	}
}