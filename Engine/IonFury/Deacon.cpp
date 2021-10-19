#include "stdafx.h"
#include "Deacon.h"
#include "DeaconSpriteAnimator.h"
#include "PhysicsInitialize.h"
#include "Player.h"
#include "BloodEffect.h"
#include "PhysicsLayers.h"
#include "DeaconflyEffect.h"

void Deacon::Awake()
{
	Monster::Awake();

	m_hp = 25;
	m_moveSpeed = 4.f;

	m_body->mass = 1.f;
	//질량

	m_body->interpolate = Interpolate::Extrapolate;
	// 보간

	m_body->useGravity = false;
	// 중력

	m_body->sleepThresholder = 1.f;
	//절전 모드로 전환될 수 있습니다. Rigidbody가 잠자기 상태일 때 프레임마다 업데이트되지 않으므로 리소스 집약적이지 않습니다. 리지드바디의 운동 에너지를 질량으로 나눈 값이 이 임계값보다 낮으면 수면 후보입니다.

	m_rendererObj->transform->scale = Vec3::one() * 5.0f;

	m_rendererObj->transform->localPosition = Vec3(0, -2.5f, 0);

	m_renderer = CreateRenderer();

	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;
	//빌보드 

	m_attackCount = 4;

	m_animator = m_renderer->gameObject->AddComponent<DeaconSpriteAnimator>();


}

void Deacon::FixedUpdate()
{
	//물리 업데이트 
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

void Deacon::Update()
{
	Monster::Update();

	Moving(movingtype);

	m_animator->SetAngle(AngleToPlayerWithSign());//플레이어기준 어디에있는지 ~몬스터 가 보는 방향과 플레이어 방향 사이의 크기 에서 보여줄 스프라이트 출력시키게 해주는거

	if (m_animator->IsPlayingShoot())
	{
		m_defaultEmissive = Color::white();     //데미지 이펙트 컬러
	}
	else
	{
		m_defaultEmissive = Color::black();
	}

	// 몬스터의 사망이 확인되었을때
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


	if (!m_isDead)
		Effect();
}

void Deacon::OnDestroy()
{
	Monster::OnDestroy();


}

Collider* Deacon::InitializeCollider(GameObject* colliderObj)
{
	//{
	//	auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
	//	renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}

	/*colliderObj->transform->localScale = Vec3::one() * 2.0f;
	colliderObj->transform->position = m_body->transform->position;*/

	return colliderObj->AddComponent<SphereCollider>();
}

void Deacon::OnDamage(DamageParameters& params)
{
	if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
	{
		GameObject* bloodEffectObj = CreateGameObject();
		bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
		bloodEffectObj->AddComponent<BloodEffect>();
	}


	params.force = Vec3::zero();

}

void Deacon::OnDead(bool& dead, DamageParameters& params)
{
	m_animator->PlayDie();

	m_hasTargetCoord = false;
	m_attackCount = 0;
	m_moveSpeed = 0;
	m_body->useGravity = true;
	//transform->position -= Vec3(0.f, 0.1f, 0.f);

	//int dieIndex = rand() % (int)DeaconSpriteAnimator::DIE::MAX;


	//if (params.damageType == MonsterDamageType::Explosion)
	//{
	//	dieIndex = (int)MonsterDamageType::Explosion;
	//}


	m_realdead = true;

}

void Deacon::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;
}

void Deacon::Attack()
{
	if (m_attackCount > 0)
	{
		--m_attackCount;
		m_animator->PlayShoot();

		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

		ShootToPlayer();
	}

	else if (!m_isDead && m_attackCount <= 0)
	{
		m_animator->PlayDefaultAnimation();
	}
}

void Deacon::Explosion()
{

}

void Deacon::Moving(MovingType type)
{
	if (!m_hasTargetCoord)
	{
		return;
	}

	const Vec3& DeaconPos = transform->position;

	Vec3 forward = Player::GetInstance()->transform->position - DeaconPos;
	forward.y = 0;
	forward.Normalize();

	transform->forward = forward;

	Vec3 xzDeaconPos = Vec3(DeaconPos.x, 0, DeaconPos.z);

	float distance = Vec3::Distance(xzDeaconPos, m_targetCoord);

	if (distance > 1.f) //거리 비교
	{
		//벽이랑 몬스터 체크 

		PhysicsRay ray(transform->position, Vec3::down(), sqrtf(0.1f));
		RaycastHit hit;

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster) ,PhysicsQueryType::Collider, m_body))
		{
			float angle = Vec3::Angle(hit.normal, Vec3::up());

			if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain)
			{
				m_hasTargetCoord = false;
				m_ground = true;

				return;
			}
			else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
			{
				m_hasTargetCoord = false;
				return;
			}
		}
		Vec3 acceleration = forward * m_moveSpeed;
		float random = (rand() % 4) + 1;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(random));
		velocity.y = -m_body->velocity.y;
		m_body->velocity = velocity;


		if (Vec3::Distance(xzDeaconPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 2.5f)
		{
			// 이전 몬스터 좌표와 현재 몬스터 좌표의 거리를 비교해서
			// 지정한 거리 이내이면
			// 몬스터가 걸려서 움직이지 못한다고 판단하여 목표 지점을 없앱니다.
			m_hasTargetCoord = false;
			//return;
		}

		// 현재 위치를 저장합니다.
		m_beforeCoord = transform->position;
		m_beforeCoord.y = 0;
		if (m_hp < 10)
		{
			Attack(); //공격
		}

	}
	else
	{
		// 저정한 거리보다 가까운 경우에는 목표 지점을 없앱니다.
		m_hasTargetCoord = false;
	}
}

void Deacon::DeadPosSet()
{
	const Vec3& DeaconPos = transform->position;

	Vec3 forward = Player::GetInstance()->transform->position - DeaconPos;
	forward.y = 0;
	forward.Normalize();

	transform->forward = forward;

	Vec3 xzDeaconPos = Vec3(DeaconPos.x, 0, DeaconPos.z);

	float distance = Vec3::Distance(xzDeaconPos, m_targetCoord);

	PhysicsRay ray(transform->position, Vec3::down(), sqrtf(0.3f));
	RaycastHit hit;

	if (distance > 0.5f) //거리 비교
	{
		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
		{
			float angle = Vec3::Angle(hit.normal, Vec3::down());

			if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain && angle > 55 && angle < 65)
			{
				m_body->useGravity = true;
				m_body->mass = 5.f;

			}
		}
	}


	m_isDead = true;
	m_realdead = false;

}

void Deacon::Effect()
{
	createEffect += Time::DeltaTime();

	if (createEffect > 0.2f)
	{
		auto obj = CreateGameObject();
		obj->transform->position = transform->position;
		obj->transform->forward = transform->forward;
		obj->AddComponent<DeaconflyEffect>();
		createEffect = 0;

	}
}
void Deacon::ShootToPlayer()
{
	Vec3 mosterToPlayer = Player::GetInstance()->transform->position - transform->position;
	mosterToPlayer.Normalize();
	Player::GetInstance()->TakeDamage(1);
}