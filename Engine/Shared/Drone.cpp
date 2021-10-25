#include "shared_stdafx.h"
#include "Drone.h"
#include "DroneSpriteAnimator.h"
#include "PhysicsLayers.h"
#include "Player.h"
#include "DroneExplosion.h"
#include "DroneSmoke.h"
#include "BloodEffect.h"
#include "SoundMgr.h"

void Drone::Awake()
{
	Monster::Awake();

	m_hp = 10;
	m_moveSpeed = 4.0f;

	m_body->mass = 1.f;
	m_body->interpolate = Interpolate::Extrapolate;
	m_body->useGravity = false;
	m_body->sleepThresholder = 1.0f;

	m_renderer = CreateRenderer();

	m_rendererObj->transform->scale = Vec3::one() * 4.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -2.f, 0);
	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;

	m_animator = m_renderer->gameObject->AddComponent<DroneSpriteAnimator>();

}

void Drone::FixedUpdate()
{
	Monster::FixedUpdate();

	if (Time::FixedTimeScale() == 0)
		return;

	if (m_isDead)
	{
		return;
	}

	DistanceCheck();

	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Drone::Update()
{
	Monster::Update();

	m_animator->SetAngle(AngleToPlayerWithSign());

	if (Time::TimeScale() == 0)
		return;

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


	Moving(movingtype);

	Attack();

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

	if (Time::TimeScale() == 0)
		return;
}

Collider* Drone::InitializeCollider(GameObject* colliderObj)
{
	//{
	//	auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}

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
}

void Drone::OnDead(bool& dead, DamageParameters& params)
{
	Explosion();

	gameObject->Destroy();
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
		Vec3 playerPos = Player::GetInstance()->transform->position;
		float distance = Vec3::Distance(xzdronePos, playerPos);

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

		const Vec3& dronePos = transform->position;

		float distanceY = Vec3::Distance(xzdronePos, dronePos);			// y ±Ê¿Ã


		if (m_deltatime < 1.5f)
		{
			if (distanceY < 10.1f)
				transform->position += transform->up * m_moveSpeed * Time::DeltaTime();
		}
		else
		{
			transform->position += transform->up * m_moveSpeed * -Time::DeltaTime();

			if (m_deltatime > 3.f)
			{
				m_deltatime = 0.f;
				//movingtype = (MovingType)2;
				movingtype = (MovingType)(rand() % unsigned int(Drone::MovingType::Max));
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

		//const Vec3& dronePos = transform->position;
		//Vec3 playerPos = Player::GetInstance()->transform->position;
		//Vec3 monsterToPlayer = playerPos - dronePos;
		//monsterToPlayer.Normalize();
		//transform->forward = monsterToPlayer;
		////float distanceP = Vec3::Distance(playerPos, dronePos);

		//Vec3 velocity = monsterToPlayer * m_moveSpeed;
		//velocity.y = 0;
		//m_body->velocity = velocity;

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
				//movingtype = MovingType::Attack;
				m_deltatime = 0.f;
				movingtype = MovingType::Trace;

			}
		}

	}
	break;
	case Drone::MovingType::Attack:
	{
		m_attackCount = 10;

		//movingtype = (MovingType)4;
		movingtype = (MovingType)(rand() % unsigned int(Drone::MovingType::Max));
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


		if (m_damageToPlayer)
		{
			ShootToPlayer();
		}
	}

}

void Drone::Explosion()
{
	{
		GameObject* effectObj = CreateGameObject();
		effectObj->transform->position = transform->position;
		effectObj->AddComponent<DroneExplosion>();
	}
}

void Drone::ShootToPlayer()
{
	Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayer.Normalize();
	Player::GetInstance()->TakeDamage(1);
	m_damageToPlayer = false;
}

void Drone::DistanceCheck()
{
	const Vec3& dronePos = transform->position;
	Vec3 xzdronePos = Vec3(dronePos.x, 0, dronePos.z);

	Vec3 forward = m_targetCoord - dronePos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;

	float distance = Vec3::Distance(xzdronePos, m_targetCoord);

	if (distance > 2.1f)
	{
		PhysicsRay ray(transform->position, forward.normalized(), sqrtf(10.0f));
		RaycastHit hit;

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Player), PhysicsQueryType::Collider, m_body))
		{
			if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Player)
			{
				m_damageToPlayer = true;
			}
		}
	}
}
