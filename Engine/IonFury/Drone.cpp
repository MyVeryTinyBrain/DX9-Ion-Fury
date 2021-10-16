#include "stdafx.h"
#include "Drone.h"
#include "DroneSpriteAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"
#include "DroneExplosion.h"
#include "DroneSmoke.h"
#include "BloodEffect.h"

void Drone::Awake()
{
	Monster::Awake();

	m_hp = 5;
	m_moveSpeed = 4.0f;

	m_body->mass = 1.f;
	m_body->interpolate = true;
	m_body->useGravity = false;
	m_body->sleepThresholder = 1.0f;

	m_rendererObj->transform->scale = Vec3::one() * 4.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -0.5f, 0);
	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;


	m_animator = m_rendererChildObj->AddComponent<DroneSpriteAnimator>();

}

void Drone::FixedUpdate()
{
	Monster::FixedUpdate();

	if (m_isDead)
	{
		return;
	}

	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Drone::Update()
{
	Monster::Update();

	if (m_isDead)
	{
		return;
	}

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

	//Moving(movingtype);

	Attack();

	m_animator->SetAngle(AngleToPlayerWithSign());

	if (m_animator->IsPlayingShoot() | m_animator->IsPlayingMoveShoot())
	{
		m_defaultEmissive = Color::white();
	}
	else
	{
		m_defaultEmissive = Color::black();
	}
}

void Drone::OnDestroy()
{
	Monster::OnDestroy();
}

Collider* Drone::InitializeCollider(GameObject* colliderObj)
{
	{
		auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	}

	colliderObj->transform->localScale = Vec3::one() * 2.0f;

	return colliderObj->AddComponent<SphereCollider>();
}

void Drone::OnDamage(DamageParameters& params)
{
	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
	{
		GameObject* bloodEffectObj = CreateGameObject();
		bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
		bloodEffectObj->AddComponent<BloodEffect>();
	}

	params.force = Vec3::zero();

	Explosion();
	// 데미지 스프라이트 없음. 
	gameObject->Destroy(); // effect!
}

void Drone::OnDead(bool& dead, DamageParameters& params)
{
	// 죽는 모션 없음. 이펙트 생성
}

void Drone::Moving(MovingType type)
{
	m_hasTargetCoord = false;


	Vec3 dronePos = transform->position;

	Vec3 forward = Player::GetInstance()->transform->position - dronePos;
	forward.Normalize();
	transform->forward = forward;

	switch (type)
	{
	case Drone::MovingType::Idle:
		movingtype = (MovingType)1;
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
			m_animator->SetDefaultAnimation(m_animator->GetIdle(), true);
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
				movingtype = (MovingType)2;
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
			m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
			m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.0f);
		}
		else
		{
			transform->position += transform->right * m_moveSpeed * -Time::DeltaTime();
			m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
			m_animator->GetRenderer()->userMesh->uvScale = Vec2(-1.f, 1.0f);
			if (m_deltatime > 6.f)
			{
				m_deltatime = 0.f;
				movingtype = (MovingType)3;
			}
		}
	}
	break;
	case Drone::MovingType::Attack:
	{
		m_attackCount = 10;

		movingtype = (MovingType)4;
	}
	break;
	case Drone::MovingType::Max:
	{
		if (m_attackCount == 1)
		{
			movingtype = (MovingType)0;
		}
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
	if (m_attackCount > 0)
	{
		--m_attackCount;

		m_animator->SetDefaultAnimation(m_animator->GetShoot(), true);
		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

	}

}

void Drone::Explosion()
{
	{
		GameObject* effectObj = CreateGameObject();
		effectObj->transform->position = transform->position;
		effectObj->AddComponent<DroneSmoke>();
	}
	{
		GameObject* effectObj = CreateGameObject();
		effectObj->transform->position = transform->position;
		effectObj->AddComponent<DroneExplosion>();
	}
}
