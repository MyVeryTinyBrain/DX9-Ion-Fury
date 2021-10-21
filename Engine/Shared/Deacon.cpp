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
	//����

	m_body->interpolate = Interpolate::Extrapolate;
	// ����

	m_body->useGravity = false;
	// �߷�

	m_body->sleepThresholder = 1.f;
	//���� ���� ��ȯ�� �� �ֽ��ϴ�. Rigidbody�� ���ڱ� ������ �� �����Ӹ��� ������Ʈ���� �����Ƿ� ���ҽ� ���������� �ʽ��ϴ�. ������ٵ��� � �������� �������� ���� ���� �� �Ӱ谪���� ������ ���� �ĺ��Դϴ�.

	m_rendererObj->transform->scale = Vec3::one() * 5.0f;

	m_rendererObj->transform->localPosition = Vec3(0, -2.3f, 0);

	m_renderer = CreateRenderer();

	m_renderer->freezeX = false;
	m_renderer->freezeZ = false;
	//������ 


	m_animator = m_renderer->gameObject->AddComponent<DeaconSpriteAnimator>();

	movingtype = MovingType::Trace;


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

	// ������ ����� Ȯ�εǾ�����
	if (m_isDead)
	{
		// �ٵ��� �ӵ��� �ſ� �۴ٸ�
		// �ٵ�� �ݶ��̴� "������Ʈ" �� �����մϴ�.
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

	//m_animator->SetAngle(AngleToPlayerWithSign());//�÷��̾���� ����ִ��� ~���� �� ���� ����� �÷��̾� ���� ������ ũ�� ���� ������ ��������Ʈ ��½�Ű�� ���ִ°�

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

		if (distance > 0.5f) //�Ÿ� ��
		{        // ������ �Ÿ����� �� ��쿡 ����˴ϴ�.
			//���̶� ���� üũ 

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
				// ���� ���� ��ǥ�� ���� ���� ��ǥ�� �Ÿ��� ���ؼ�
				// ������ �Ÿ� �̳��̸�
				// ���Ͱ� �ɷ��� �������� ���Ѵٰ� �Ǵ��Ͽ� ��ǥ ������ ���۴ϴ�.
				m_hasTargetCoord = false;
				//return;
			}

			// ���� ��ġ�� �����մϴ�.
			m_beforeCoord = transform->position;
			m_beforeCoord.y = 0;

		}
		else
		{
			// ������ �Ÿ����� ����� ��쿡�� ��ǥ ������ ���۴ϴ�.
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
			// �÷��̾ �þ߰� ���� �ִٸ� �����մϴ�.
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
					Attack(); //����
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
