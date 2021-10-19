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
	//����

	m_body->interpolate = Interpolate::Extrapolate;
	// ����

	m_body->useGravity = false;
	// �߷�

	m_body->sleepThresholder = 1.f;
	//���� ���� ��ȯ�� �� �ֽ��ϴ�. Rigidbody�� ���ڱ� ������ �� �����Ӹ��� ������Ʈ���� �����Ƿ� ���ҽ� ���������� �ʽ��ϴ�. ������ٵ��� � �������� �������� ���� ���� �� �Ӱ谪���� ������ ���� �ĺ��Դϴ�.

	m_rendererObj->transform->scale = Vec3::one() * 5.0f;

	m_rendererObj->transform->localPosition = Vec3(0, -2.5f, 0);

	m_renderer = CreateRenderer();

	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;
	//������ 

	m_attackCount = 4;

	m_animator = m_renderer->gameObject->AddComponent<DeaconSpriteAnimator>();


}

void Deacon::FixedUpdate()
{
	//���� ������Ʈ 
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

	if (m_ground)
	{
		m_body->SetRotationLockAxis(PhysicsAxis::All, true);
		m_body->SetTranslationLockAxis(PhysicsAxis::All, true);
	}

	//if (m_isDead)
	//{
	//	if (m_body)
	//	{
	//		m_body->Destroy();
	//		m_collider->Destroy();
	//		m_body = nullptr;
	//		m_collider = nullptr;
	//	}
	//}
	Moving(movingtype);

	m_animator->SetAngle(AngleToPlayerWithSign());//�÷��̾���� ����ִ��� ~���� �� ���� ����� �÷��̾� ���� ������ ũ�� ���� ������ ��������Ʈ ��½�Ű�� ���ִ°�

	if (m_animator->IsPlayingShoot())
	{
		m_defaultEmissive = Color::white();     //������ ����Ʈ �÷�
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

	// m_animator->OnDeadAnimated -= Function<void()>(this, &Gunner::OnDeadAnimated);

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
	//transform->position -= Vec3(0.f, 0.1f, 0.f);

	int dieIndex = rand() % (int)DeaconSpriteAnimator::DIE::MAX;


	if (params.damageType == MonsterDamageType::Explosion)
	{
		dieIndex = (int)MonsterDamageType::Explosion;
	}


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

	if (distance > 1.f) //�Ÿ� ��
	{
		//���̶� ���� üũ 

		PhysicsRay ray(transform->position, Vec3::down(), sqrtf(0.1f));
		RaycastHit hit;

		if (Physics::Raycast(hit, ray, (1 << (PxU32)PhysicsLayers::Terrain), PhysicsQueryType::Collider, m_body))
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
		Vec3 acceleration = forward * m_moveSpeed;
		float random = (rand() % 4) + 1;
		Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(random));
		velocity.y = -m_body->velocity.y;
		m_body->velocity = velocity;


		if (Vec3::Distance(xzDeaconPos, m_beforeCoord) <= m_moveSpeed * Time::FixedDeltaTime() * 2.5f)
		{
			// ���� ���� ��ǥ�� ���� ���� ��ǥ�� �Ÿ��� ���ؼ�
			// ������ �Ÿ� �̳��̸�
			// ���Ͱ� �ɷ��� �������� ���Ѵٰ� �Ǵ��Ͽ� ��ǥ ������ ���۴ϴ�.
			m_hasTargetCoord = false;
			//return;
		}

		// ���� ��ġ�� �����մϴ�.
		m_beforeCoord = transform->position;
		m_beforeCoord.y = 0;
		if (m_hp < 10)
		{
			Attack(); //����
		}

	}
	else
	{
		// ������ �Ÿ����� ����� ��쿡�� ��ǥ ������ ���۴ϴ�.
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

	if (distance > 0.5f) //�Ÿ� ��
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


	/*for (int i = 0; i < 3; ++i)
{
	m_rendererObj->transform->localPosition -= Vec3(0, i + 0.4, 0);
}*/


//float randomPull = float(rand() % 1000) / 1000.0f;
//randomPull *= 0.01f;
//transform->position = transform->position + transform->position.normalized() * (0.01f + randomPull);
//transform->forward = transform->position.normalized();

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







//switch (type)
//{
//case Deacon::MovingType::Idle:
//{
//    movingtype = (MovingType)1;
//}
//break;
//case Deacon::MovingType::Trace:
//{
//    Vec3 xzdronePos = Vec3(DeaconPos.x, 0, DeaconPos.z);
//    float distance = Vec3::Distance(xzdronePos, Player::GetInstance()->transform->position);
//
//    if (distance > 8.f)
//        m_distance = true;
//    else
//        m_distance = false;
//
//    if (m_distance)
//    {
//        m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
//        Vec3 targetCoord = Player::GetInstance()->transform->position;
//        SetTargetCoord(targetCoord);
//
//        Vec3 velocity = forward * m_moveSpeed;
//        velocity.y = 0;
//        m_body->velocity = velocity;
//    }
//
//    m_deltatime += Time::DeltaTime();
//
//    if (m_deltatime < 1.5f)
//    {
//        transform->position += transform->up * m_moveSpeed * Time::DeltaTime();
//    }
//    else
//    {
//        transform->position += transform->up * m_moveSpeed * -Time::DeltaTime();
//
//        if (m_deltatime > 3.f)
//        {
//            m_deltatime = 0.f;
//            movingtype = (MovingType)2;
//        }
//    }
//}
//break;
//case Deacon::MovingType::leftRight:
//{
//    transform->up = Vec3(0, 1, 0);
//    transform->right = Vec3::Cross(transform->up, transform->forward);
//    transform->right.Normalize();
//
//    m_deltatime + Time::DeltaTime();
//
//    if (m_deltatime < 3.f)
//    {
//        transform->position += transform->right * m_moveSpeed * Time::DeltaTime();
//        m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
//        m_animator->GetRenderer()->userMesh->uvScale = Vec2(1.f, 1.f);
//
//    }
//    else
//    {
//        transform->position += transform->right * m_moveSpeed * -Time::DeltaTime();
//        m_animator->SetDefaultAnimation(m_animator->GetMove(), true);
//        m_animator->GetRenderer()->userMesh->uvScale = Vec2(-1.f, 1.0f);
//        if (m_deltatime > 6.f)
//        {
//            m_deltatime = 0.f;
//            movingtype = (MovingType)3;
//        }
//    }
//}
//break;
//case Deacon::MovingType::Attack:
//{
//    m_attackCount = 10;
//
//    movingtype = (MovingType)4;
//}
//break;
//case Deacon::MovingType::Max:
//{
//    if (m_attackCount == 1)
//    {
//        movingtype = (MovingType)0;
//    }
//}
//break;
//}