#include "shared_stdafx.h"
#include "Mutant.h"
#include "MutantSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"
#include "BloodEffect.h"
#include "MutantPoison.h"

void Mutant::Awake()
{

	Monster::Awake();
	m_moveSpeed = 0.f;
	m_hp = 20;
	m_body->mass = 10.f;
	m_body->interpolate = Interpolate::Extrapolate;
	m_body->sleepThresholder = 0.5f;
	m_body->useGravity = true;
	//m_rendererObj->transform->localPosition = Vec3(0, 0.3f, 0);


	m_attackCount = 5;
	m_rendererObj->transform->scale = Vec3::one() * 5.0f;



	m_renderer = CreateRenderer();
	m_renderer->freezeX = true;
	m_renderer->freezeZ = true;

	m_animator = m_renderer->gameObject->AddComponent<MutantSpriteAnimator>();

}

void Mutant::FixedUpdate()
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
		m_rendererObj->transform->localPosition = Vec3(0, -0.5f, 0);
		Vec3 targetCoord = Player::GetInstance()->transform->position;
		SetTargetCoord(targetCoord);
	}
}

void Mutant::Update()
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

		if (chageanimation > 2.1f)
		{
			m_hasTargetCoord = true;
			m_animator->SetDefaultAnimation(m_animator->GetWalk());
			m_moveSpeed = 2.0f;
		}
	}


	MoveToTarget();

	makePoisonDt += Time::DeltaTime();
	if (m_isDead)
	{
		// 바디의 속도가 매우 작다면
		// 바디와 콜라이더 "컴포넌트" 만 삭제합니다.
		if (m_body && m_body->IsRigidbodySleep())
		{
			m_body->Destroy();
			m_collider->Destroy();
			m_body = nullptr;
			m_collider = nullptr;
		}
		return;
	}


	if (m_hp < 10)
	{

		Attack();
		newmakepoisondt += Time::DeltaTime();

		if (newmakepoisondt > 1.5f)
		{
			m_attackCount = 7;
			Attack();
			newmakepoisondt = 0;
		}
		//			makePoisonDt = 0;
			//	}

	}

	if (m_animator->IsPlayingShoot())
	{
		m_defaultEmissive = Color::white();
	}
	else
	{
		m_defaultEmissive = Color::black();
	}

}

void Mutant::OnDestroy()
{
	Monster::OnDestroy();

	//m_animator->OnDeadAnimated -= Function<void()>(this, &Mutant::OnDeadAnimated);

	if (Time::TimeScale() == 0)
		return;
}

Collider* Mutant::InitializeCollider(GameObject* colliderObj)
{
	{
		auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	}

	colliderObj->transform->scale = Vec3(1.f, 1.1f, 1.f);


	return colliderObj->AddComponent<SphereCollider>();
}

void Mutant::OnDamage(DamageParameters& params)
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

void Mutant::OnDead(bool& dead, DamageParameters& params)
{
	m_moveSpeed = 0;
	//m_body->useGravity = true;
	m_hasTargetCoord = false;
	m_attackCount = 0;

	int dieIndex = rand() % (int)MutantSpriteAnimator::DIE_MUTANT::MAX;


	if (params.damageType == MonsterDamageType::Explosion)
	{
		dieIndex = (int)MonsterDamageType::Explosion;
	}

	m_animator->PlayDie((MutantSpriteAnimator::DIE_MUTANT)dieIndex);
}

void Mutant::MoveToTarget()
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

void Mutant::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;

	Vec3 forward = xzCoord - transform->position;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
}

void Mutant::Attack()
{
	if (m_attackCount > 0)
	{

		--m_attackCount;
		m_animator->PlayShoot();
		auto obj = CreateGameObject();
		obj->transform->position = transform->position + Vec3(0.f, 0.7f, 0.f) /*+ (-transform->right)*/;
		obj->AddComponent<MutantPoison>();
	}

}
