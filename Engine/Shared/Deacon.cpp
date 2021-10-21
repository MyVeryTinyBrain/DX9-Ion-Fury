#include "shared_stdafx.h"
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

	m_rendererObj->transform->localPosition = Vec3(0, -2.3f, 0);

	m_renderer = CreateRenderer();

	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;
	//빌보드 


	m_animator = m_renderer->gameObject->AddComponent<DeaconSpriteAnimator>();

	movingtype = MovingType::Trace;


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

	if (m_animator->IsPlayingDamage())
	{
		return;
	}

	float angleToPlayer = AngleToPlayerWithSign();

	Moving(movingtype);

	//m_animator->SetAngle(AngleToPlayerWithSign());//플레이어기준 어디에있는지 ~몬스터 가 보는 방향과 플레이어 방향 사이의 크기 에서 보여줄 스프라이트 출력시키게 해주는거

	if (m_animator->IsPlayingShoot())
	{
		m_defaultEmissive = Color::white();     //데미지 이펙트 컬러
	}
	else
	{
		m_defaultEmissive = Color::black();
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
	{
		auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
		renderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInTransparentGreenTexture));
		renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	}

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

	//	m_realdead = true;

}

void Deacon::SetTargetCoord(Vec3 xzCoord)
{
	m_hasTargetCoord = true;
	m_targetCoord = xzCoord;
	m_targetCoord.y = 0;

	Vec3 forward = xzCoord - transform->position;
	forward.y = 0;
	forward.Normalize();
	transform->forward = forward;
}

void Deacon::Attack()
{

	if (m_attackCount > 0)
	{
		m_animator->PlayShoot();
		ShootToPlayer();
		--m_attackCount;

		Vec3 forward = Player::GetInstance()->transform->position - transform->position;
		forward.y = 0;
		forward.Normalize();
		transform->forward = forward;

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

	//Vec3 forwardY = Player::GetInstance()->transform->position - DeaconPos;
	Vec3 forward = m_targetCoord - DeaconPos;
	forward.y = 0;
	forward.Normalize();
	Vec3 playerPos = Player::GetInstance()->transform->position;
	transform->forward = forward;
	Vec3 xzDeaconPos = Vec3(DeaconPos.x, 0, DeaconPos.z);
	float distance = Vec3::Distance(xzDeaconPos, m_targetCoord);


	switch (type)
	{
	case Deacon::MovingType::Idle:
	{
		movingtype = (MovingType)1;
	}
	break;
	case Deacon::MovingType::Trace:
	{

		if (distance > 0.5f) //거리 비교
		{        // 지정한 거리보다 먼 경우에 실행됩니다.
			//벽이랑 몬스터 체크 

			PhysicsRay ray(transform->position, Vec3::down(), sqrtf(3.1f));
			RaycastHit hit;

			if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
			{

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

		}
		else
		{
			// 저정한 거리보다 가까운 경우에는 목표 지점을 없앱니다.
			m_hasTargetCoord = false;
		}

		Vec3 acceleration = forward * m_moveSpeed;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(5));
		velocity.y = -m_body->velocity.y;
		m_body->velocity = velocity;

		m_deltatime += Time::DeltaTime();
		if (m_deltatime > 4.f)
		{
			movingtype = (MovingType)(rand() % unsigned int(Deacon::MovingType::Max));
		}
	}
	break;
	case Deacon::MovingType::leftRight:
	{
		m_animator->PlayDefaultAnimation();

		Vec3 xzDeaconPos = Vec3(DeaconPos.x, 0, DeaconPos.z);
		float distance = Vec3::Distance(xzDeaconPos, Player::GetInstance()->transform->position);

		transform->up = Vec3(0, 1, 0);
		transform->right = Vec3::Cross(transform->up, transform->forward);
		transform->right.Normalize();

		m_deltatime += Time::DeltaTime();

		float distanceP = Vec3::Distance(playerPos, DeaconPos);

		if (distanceP < 4.1f)
		{
			if (m_deltatime < 2.f)
			{
				Vec3 acceleration = forward * m_moveSpeed;
				Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(5));
				velocity.y = -m_body->velocity.y;
				m_body->velocity = velocity;

				//m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.0f);
			}
			else
			{
				Vec3 acceleration = forward * m_moveSpeed;
				Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(5));
				velocity.y = -m_body->velocity.y;
				m_body->velocity = velocity;

				//m_animator->GetRenderer()->userMesh->uvScale = Vec2(-1.f, 1.0f);
				if (m_deltatime > 3.f)
				{
					m_deltatime = 0.f;
					movingtype = (MovingType)(rand() % unsigned int(MovingType::Max));
				}
			}
		}

	}
	break;
	case Deacon::MovingType::Attack:
	{
		float angleToPlayer = AngleToPlayerWithSign();
		{
			// 플레이어가 시야각 내에 있다면 공격합니다.
			Vec3 temp;
			if (Abs(angleToPlayer) < 30 && (m_animator->IsPlayingMove()))
			{
				int attack = rand() % 2;
				if (attack)
				{
					MovingType();
				}
				else
				{
					movingtype = Deacon::MovingType::Attack;
					m_attackCount = 3;
					Attack(); //공격
				}
			}
			else
			{
				movingtype = (MovingType)(rand() % unsigned int(Deacon::MovingType::Max));
			}
		}

		//m_attackCount = 3;
		//movingtype = (MovingType)(rand() % unsigned int(MovingType::Max));
	}
	break;
	}
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

float Deacon::GetXZDistance(const Vec3& point) const
{
	Vec3 posxz = transform->position;
	posxz.y = 0;

	Vec3 targetxz = point;
	targetxz.y = 0;

	return Vec3::Distance(posxz, targetxz);
}

Vec3 Deacon::GetXZDirection(const Vec3& point) const
{
	Vec3 posxz = transform->position;
	posxz.y = 0;

	Vec3 targetxz = point;
	targetxz.y = 0;

	Vec3 rel = targetxz - posxz;
	Vec3 dir = rel.normalized();

	return dir;
}
