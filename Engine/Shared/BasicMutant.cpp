#include "shared_stdafx.h"
#include "BasicMutant.h"
#include "BasicMutantSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"
#include "SoundMgr.h"

void BasicMutant::Awake()
{

	Monster::Awake();

	m_hp = 1000; //15
	AttackHp = 700; //7
	m_moveSpeed = 0;
	m_body->mass = 5.f;
	m_body->interpolate = Interpolate::Extrapolate;
	m_body->sleepThresholder = 0.5f;
	m_body->useGravity = true;

	m_rendererObj->transform->localPosition = Vec3(0, -0.8f, 0);


	m_attackCount = 10000;
	m_rendererObj->transform->scale = Vec3::one() * 5.0f;


	m_renderer = CreateRenderer();

	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;

	m_animator = m_renderer->gameObject->AddComponent<BasicMutantSpriteAnimator>();
}

void BasicMutant::FixedUpdate()
{
	Monster::FixedUpdate();

	if (Time::FixedTimeScale() == 0)
		return;

	if (m_isDead)
	{
		return;
	}

	if (!m_hasTargetCoord)
	{
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}


	if (!hittt && m_animator->GetCurrentAnimation() == m_animator->GetAttack())
	{
		ColliderCheck();
	}


}

void BasicMutant::Update()
{
	Monster::Update();

	if (m_isDead)
	{
		return;
	}

	if (Time::TimeScale() == 0)
		return;

	if (create)
	{
		SoundMgr::Play(L"../SharedResource/Sound/zombie/zombie_roam_3.ogg", CHANNELID::BASICMUTANTCREATE);

		createdt += Time::DeltaTime();
		m_hasTargetCoord = false;
		if (createdt >= 3.f)
		{
			create = false;
			createdt = 0;
			m_animator->SetDefaultAnimation(m_animator->GetWalk());
		}
	}

	else if (!create && m_animator->GetCurrentAnimation() == m_animator->GetWalk())
	{
		m_moveSpeed = 1.f;
	}

	if (m_hp < AttackHp)
	{
		if (hittt)
		{
			//m_animator->PlayWalk();
			m_moveSpeed = 1.f;
			pattern += Time::DeltaTime();
			if (pattern > 1.5f)
			{
				pattern = 0;
				hittt = false;
			}
		}
		else if (!hittt)
		{
			createdt += Time::DeltaTime();
			if (createdt > 0.5f)
			{
				Attack();
				createdt = 0;
			}
		}
		else 
			m_animator->PlayWalk();
	}

	MoveToTarget();

	//if (m_animator->IsPlayingAttack())
	//{
	//	m_defaultEmissive = Color::white();
	//}
	//else
	//{
	//	m_defaultEmissive = Color::black();
	//}

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
	//{
	//	auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}

	m_CapsuleCollider = colliderObj->AddComponent<CapsuleCollider>();
	m_CapsuleCollider->transform->localScale = Vec3::one() * 0.8f;
	//m_sphereCollider->OnCollisionEnter += Function<void(const CollisionEnter&)>(this, &Spider::OnCollisionEnter);
	
	
	return m_CapsuleCollider;
}

void BasicMutant::OnDamage(DamageParameters& params)
{
	hitdamage = true;
	m_hasTargetCoord = false;

	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
	{
		SoundMgr::Play(L"../SharedResource/Sound/zombie/zombie_hit_2.ogg", CHANNELID::BASICMUTANTHIT);

		GameObject* bloodEffectObj = CreateGameObject();
		bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
		bloodEffectObj->AddComponent<BloodEffect>();
	}
}

void BasicMutant::OnDead(bool& dead, DamageParameters& params)
{
	//m_body->useGravity = true;
	m_moveSpeed = 0;
	int dieIndex = rand() % (int)BasicMutantSpriteAnimator::DIE_BasicMutant::DIE_EXPLOSION;


	if (params.damageType == MonsterDamageType::Explosion)
	{
		dieIndex = (int)BasicMutantSpriteAnimator::DIE_BasicMutant::DIE_EXPLOSION;
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

	if (distance > 0.1f)
	{
		PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
		RaycastHit hit;

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
		{
			float angle = Vec3::Angle(hit.normal, Vec3::up());

			if (hit.collider->layerIndex == (PxU32)PhysicsLayers::Terrain && angle > 85 && angle < 95)
			{
				hittt = true;
				m_hasTargetCoord = false;
				return;
			}
			else if (hit.collider->layerIndex == (PxU32)PhysicsLayers::Monster)
			{
				m_hasTargetCoord = false;
				return;
			}
		}


		Vec3 acceleration = forward * m_moveSpeed;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
		velocity.y = m_body->velocity.y;
		m_body->velocity = velocity;
		noAttack = false;


		if (Vec3::Distance(xzMutantPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
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
		SoundMgr::Play(L"../SharedResource/Sound/zombie/zombie_swing_2.ogg", CHANNELID::BASICMUTANTATTACK);

		m_animator->PlayAttack();
		m_moveSpeed = 6.f;
		damage = 1;
		--m_attackCount;
	}
}
void BasicMutant::ShootToPlayer()
{
	Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayer.Normalize();
	Player::GetInstance()->TakeDamage(damage);
	--damage;
	m_animator->PlayWalk();
	hittt = true;
	hitdamage = false;
	if (damage <= 0)
		return;
}

void BasicMutant::OnDeadAnimated()
{
}

void BasicMutant::ColliderCheck()
{
	Collider* collider = Physics::OverlapSphere(
		0.6f,
		transform->position,
		(1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Player),
		PhysicsQueryType::Collider);


	if (collider)
	{
		notPlayAttack += Time::DeltaTime();
		if (collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
		{
		}
		else if (collider->layerIndex == (uint8_t)PhysicsLayers::Player)
		{
			ShootToPlayer();
		}
	}
}

void BasicMutant::AttackAfter()
{
	m_moveSpeed = 1.0f;
	m_animator->PlayWalk();
	//m_hasTargetCoord = true;
	//m_animator->SetDefaultAnimation(m_animator->GetWalk());
}
