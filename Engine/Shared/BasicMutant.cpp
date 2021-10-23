#include "shared_stdafx.h"
#include "BasicMutant.h"
#include "BasicMutantSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"

void BasicMutant::Awake()
{

	Monster::Awake();

	m_hp = 15;
	m_moveSpeed = 2.0f;
	m_body->mass = 3.0f;
	m_body->interpolate = Interpolate::Extrapolate;
	m_body->sleepThresholder = 0.5f;
	m_body->useGravity = true;

	//m_rendererObj->transform->localPosition = Vec3(0, -0.8f, 0);


	m_attackCount = 10;
	m_rendererObj->transform->scale = Vec3::one() * 5.0f;


	m_renderer = CreateRenderer();

	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;

	m_animator = m_renderer->gameObject->AddComponent<BasicMutantSpriteAnimator>();
	m_animator->OnDeadAnimated += Function<void()>(this, &BasicMutant::OnDeadAnimated);
}

void BasicMutant::FixedUpdate()
{
	Monster::FixedUpdate();

	if (Time::FixedTimeScale() == 0)
		return;

	if (m_animator->GetCurrentAnimation() == m_animator->GetAttack())
	{
		ColliderCheck();
	}

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

void BasicMutant::Update()
{
	Monster::Update();

	m_animator->SetAngle(AngleToPlayerWithSign());

	if (Time::TimeScale() == 0)
		return;


	if (create)
	{
		m_moveSpeed = 0.f;
		m_hasTargetCoord = false;
		m_animator->SetDefaultAnimation(m_animator->GetCreate());
		//m_animator->PlayCreate();
		create = false;

		//transform->position = Vec3()
	}
	else if (!create)
	{
		chageanimation += Time::DeltaTime();

		if (chageanimation > 2.f)
		{
			m_hasTargetCoord = true;
			m_animator->SetDefaultAnimation(m_animator->GetWalk());
			//if (m_hp > 10)
			//	m_moveSpeed = 2.0f;
		}
	}


	MoveToTarget();

	if (m_hp < 8)
	{
		m_moveSpeed = 8.f;
		Attack();
	}

	if (m_animator->IsPlayingAttack())
	{
		m_defaultEmissive = Color::white();
	}
	else
	{
		m_defaultEmissive = Color::black();
	}

}

void BasicMutant::OnDestroy()
{
	Monster::OnDestroy();

	//m_animator->OnDeadAnimated -= Function<void()>(this, &BasicMutant::OnDeadAnimated);

	if (Time::TimeScale() == 0)
		return;
}

Collider* BasicMutant::InitializeCollider(GameObject* colliderObj)
{
	{
		auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
		renderer->transform->localPosition = Vec3(0, -0.4f, 0);
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	}

	colliderObj->transform->scale = Vec3(0.7f, 1.1f, 0.7f);
	//colliderObj->transform->localPosition = Vec3(0.f, 5.f, 0.f);

	return colliderObj->AddComponent<SphereCollider>();
}

void BasicMutant::OnDamage(DamageParameters& params)
{
	m_hasTargetCoord = false;

	//switch (params.damageType)
	//{
	//case MonsterDamageType::Bullet:
	//	m_moveSpeed = 0.f;
	//	break;
	//case MonsterDamageType::Explosion:
	//	m_moveSpeed = 0.f;
	//	break;
	//case MonsterDamageType::Zizizik:
	//	//m_animator->SetDefaultAnimation(m_animator->GetDamage(), true);
	//	break;
	//}

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
}

void BasicMutant::OnDead(bool& dead, DamageParameters& params)
{
	//m_body->useGravity = true;
	int dieIndex = rand() % (int)BasicMutantSpriteAnimator::DIE_BasicMutant::MAX;


	if (params.damageType == MonsterDamageType::Explosion)
	{
		dieIndex = (int)MonsterDamageType::Explosion;
	}

	m_animator->PlayDie((BasicMutantSpriteAnimator::DIE_BasicMutant)dieIndex);


	m_hasTargetCoord = false;
	m_attackCount = 0;

}

void BasicMutant::MoveToTarget()
{
	if (!m_hasTargetCoord)
		return;

	const Vec3& MutantrPos = transform->position;
	Vec3 forward = m_targetCoord - MutantrPos;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;

	Vec3 xzMutantPos = Vec3(MutantrPos.x, 0, MutantrPos.z);
	float distance = Vec3::Distance(xzMutantPos, m_targetCoord);

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
				m_animator->IsPlayingWalk();
				return;
			}
			else if (hit.collider->layerIndex == (PxU32)PhysicsLayers::Monster)
			{
				m_hasTargetCoord = false;
				m_animator->IsPlayingWalk();
				return;
			}
		}


		Vec3 acceleration = forward * m_moveSpeed;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
		velocity.y = m_body->velocity.y;
		m_body->velocity = velocity;


		if (Vec3::Distance(xzMutantPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
		{
			m_hasTargetCoord = false;
			m_animator->IsPlayingWalk();
			return;
		}

		m_beforeCoord = transform->position;
		m_beforeCoord.y = 0;
		m_animator->IsPlayingWalk();

	}
	else
	{
		m_hasTargetCoord = false;
		m_animator->IsPlayingWalk();
	}
}

void BasicMutant::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;

	Vec3 forward = xzCoord - transform->position;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
}

void BasicMutant::Attack()
{
	if (m_attackCount > 0)
	{
		m_animator->PlayAttack();
		--m_attackCount;
	}
}
void BasicMutant::ShootToPlayer()
{
	Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayer.Normalize();
	Player::GetInstance()->TakeDamage(1);
	transform->position += Vec3(0.f,0.f,0.7f);
	//SetAttack = false;
	m_animator->IsPlayingWalk();
}

void BasicMutant::OnDeadAnimated()
{
}

void BasicMutant::ColliderCheck()
{
	Collider* collider = Physics::OverlapSphere(
		transform->position,
		0.6f,
		(1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Player),
		PhysicsQueryType::Collider);


	if (collider)
	{
		if (collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
		{
		}
		else if (collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{
			ShootToPlayer();
		}
	}
}
