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


	Attack(); //공격

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

	//Vec3 forward = Player::GetInstance()->transform->position - DeaconPos;
	Vec3 forward = m_targetCoord - DeaconPos;
	forward.y = 0;
	forward.Normalize();

	transform->forward = forward;

	switch (type)
	{
	case Deacon::MovingType::Idle:
	{
		movingtype = (MovingType)1;
	}
	break;
	case Deacon::MovingType::Trace:
	{
		//angle();
		m_animator->PlayDefaultAnimation();

		Vec3 xzDeaconePos = Vec3(DeaconPos.x, 0, DeaconPos.z);
		float distance = Vec3::Distance(xzDeaconePos, Player::GetInstance()->transform->position);

		//if (distance > 2.f)
		//	m_distance = true;
		//else
		//	m_distance = false;

		if (distance > 2.f)
		{
			////m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
			//Vec3 targetCoord = Player::GetInstance()->transform->position;
			//SetTargetCoord(targetCoord);

			//Vec3 velocity = forward * m_moveSpeed;
			//velocity.y = 0;
			//m_body->velocity = velocity;

			PhysicsRay ray(transform->position, forward.normalized(), sqrtf(2.0f));
			RaycastHit hit;
			if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain) | (1 << (PxU32)PhysicsLayers::Monster), PhysicsQueryType::Collider, m_body))
			{
				float angle = Vec3::Angle(hit.normal, Vec3::up());
				if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Terrain && angle > 85 && angle < 95)
				{
					// 충돌한 콜라이더가 Terrain인 경우에
					// 각도가 지정 각도 이내이면 벽이라고 판단하여 목표 지점을 없앱니다.
					m_hasTargetCoord = false;
					//SetBehavior(BehaviorType::Idle);
					return;
				}
				else if (hit.collider->layerIndex == (uint8_t)PhysicsLayers::Monster)
				{
					// 충돌한 콜라이더가 몬스터 콜라이더면
					// 목표 지점을 없앱니다.
					m_hasTargetCoord = false;
					//SetBehavior(BehaviorType::Idle);
					return;
				}
			}
			Vec3 acceleration = forward * m_moveSpeed;
			Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
			velocity.y = -m_body->velocity.y;
			m_body->velocity = velocity;
			if (Vec3::Distance(xzDeaconePos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 0.5f)
			{
				// 이전 몬스터 좌표와 현재 몬스터 좌표의 거리를 비교해서
				// 지정한 거리 이내이면
				// 몬스터가 걸려서 움직이지 못한다고 판단하여 목표 지점을 없앱니다.

				m_hasTargetCoord = false;
				//SetBehavior(BehaviorType::Idle);
				return;
			}
			// 현재 위치를 저장합니다.
			m_beforeCoord = transform->position;
			m_beforeCoord.y = 0;
		}
		else
		{
			// 저정한 거리보다 가까운 경우에는 목표 지점을 없앱니다.
			m_hasTargetCoord = false;
			//SetBehavior(BehaviorType::Idle);
		}

		m_deltatime += Time::DeltaTime();

		if (m_deltatime > 5.f)
			movingtype = (MovingType)(rand() % unsigned int(MovingType::Max));
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

		if (distance < 7.f)
		{

			if (m_deltatime < 2.f)
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
					movingtype = (MovingType)(rand() % unsigned int(MovingType::Max));
				}
			}
		}

		Vec3 acceleration = forward * m_moveSpeed;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(1.f)); //언덕에서 속도조절하는거 
		velocity.y = -m_body->velocity.y;
		m_body->velocity = velocity;
	}
	break;
	case Deacon::MovingType::Attack:
	{
		m_attackCount = 3;
		movingtype = (MovingType)(rand() % unsigned int(MovingType::Max));
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

void Deacon::angle()
{
	float x = transform->position.x;
	float y = transform->position.y;
	float z = transform->position.z;

	{   // Change y
		PhysicsRay ray(transform->position, Vec3::down(), sqrtf(5.f));
		RaycastHit hit;
		bool result =
			Physics::Raycast(
				hit,
				ray,
				(1 << (PxU32)PhysicsLayers::Terrain),
				PhysicsQueryType::Collider);

		if (result)
		{
			y = MathEx::Lerp(y, hit.point.y + 5.0f, Time::DeltaTime() * 3.5f);
		}
	}

	//{   // Change x, z
	//	Vec3 target = Player::GetInstance()->transform->position;
	//	float d = GetXZDistance(target);
	//	Vec3 dir = GetXZDirection(target);

	//	if (d < 3.0f)
	//	{
	//		m_body->SetTranslationLockAxis(PhysicsAxis::All, false);
	//		//m_body->useGravity = true;

	//		movingtype = (MovingType)(rand() % unsigned int(MovingType::Max));
	//		return;
	//	}
	//	else
	//	{
	//		x += dir.x * Time::DeltaTime() * 7.5f;
	//		z += dir.z * Time::DeltaTime() * 7.5f;
	//	}
	//}

	transform->position = Vec3(x, y, z);

	/*if (transform->position.y > 7.f)
	{
		for (int i = 0; i < 3; ++i)
		{
			transform->position -= Vec3(0, i * 0.5f, 0);

		}
	}

	else if (transform->position.y <= 2.f)
	{
		const Vec3& gunnerPos = transform->position;
		Vec3 forward = m_targetCoord - gunnerPos;
		forward.y = 0;
		forward.Normalize();


		Vec3 acceleration = forward * m_moveSpeed;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
		velocity.y = m_body->velocity.y;
		m_body->velocity = velocity;
	}*/
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
