#include "stdafx.h"
#include "SkullReplica.h"
#include <PhysicsLayers.h>
#include <BloodEffect.h>
#include <Player.h>
#include "SkullBall.h"

void SkullReplica::Awake()
{
    Monster::Awake();

	m_hp = 13;

    m_body->useGravity = false;
    m_body->isKinematic = true;

    m_textures[(int)DIR::FRONT] = Resource::FindAs<Texture>(L"../SharedResource/Texture/skull/fly_front.png");
    m_textures[(int)DIR::FRONT_DIAGONAL] = Resource::FindAs<Texture>(L"../SharedResource/Texture/skull/fly_front_diagonal.png");
    m_textures[(int)DIR::SIDE] = Resource::FindAs<Texture>(L"../SharedResource/Texture/skull/fly_side.png");
    m_textures[(int)DIR::BACK_DIAGONAL] = Resource::FindAs<Texture>(L"../SharedResource/Texture/skull/fly_back_diagonal.png");
    m_textures[(int)DIR::BACK] = Resource::FindAs<Texture>(L"../SharedResource/Texture/skull/fly_back.png");

    m_rendererObj->transform->localPosition = Vec3::zero();
	m_rendererObj->transform->localScale = Vec3::one() * 3.0f;

    m_renderer = CreateRenderer();
	m_renderer->transform->localPosition = Vec3::up() * 0.125f;

    m_renderer->freezeX = false;
    m_renderer->freezeY = false;
    m_renderer->freezeZ = false;

	m_defaultEmissive = Color::white();

	Vec3 local = transform->localPosition;
	if (local != Vec3::zero())
	{
		m_initLocalDirection = transform->localPosition.normalized();
	}
}

void SkullReplica::Start()
{
	Monster::Start();

	Vec3 local = transform->localPosition;
	if (local != Vec3::zero())
	{
		m_initLocalDirection = transform->localPosition.normalized();
	}
}

void SkullReplica::LateUpdate()
{
	Monster::LateUpdate();

	if (transform->parent)
	{
		Vec3 direction = transform->parent->position - transform->position;
		direction.Normalize();

		transform->forward = direction;
	}

	float angle = AngleToPlayerWithSign();

	if (!isDead && Abs(angle) < 22.5f + 45 * 0)
	{
		if (m_attackTimer <= 0)
		{
			Vec3 monsterHead = transform->position + Vec3::up() * 0.75f * 1.5f;
			Vec3 playerHead = Player::GetInstance()->perspectiveCamera->transform->position;

			Vec3 monsterToPlayer = playerHead - monsterHead;
			Vec3 dir = monsterToPlayer.normalized();

			GameObject* obj = CreateGameObject();
			obj->transform->position = monsterHead;

			SkullBall* ball = obj->AddComponent<SkullBall>();
			ball->SetVelocity(dir * 20);

			m_attackTimer = m_attackDelay;
		}

		m_attackTimer -= Time::DeltaTime();
	}

	if (Abs(angle) < 22.5f + 45 * 0)
	{
		m_renderer->SetTexture(0, m_textures[(int)DIR::FRONT]);
		ResetUVDirection();
	}
	else if (Abs(angle) < 22.5f + 45 * 1)
	{
		m_renderer->SetTexture(0, m_textures[(int)DIR::FRONT_DIAGONAL]);
		ChangeUVDirection(angle);
	}
	else if (Abs(angle) < 22.5f + 45 * 2)
	{
		m_renderer->SetTexture(0, m_textures[(int)DIR::SIDE]);
		ChangeUVDirection(angle);
	}
	else if (Abs(angle) < 22.5f + 45 * 3)
	{
		m_renderer->SetTexture(0, m_textures[(int)DIR::BACK_DIAGONAL]);
		ChangeUVDirection(angle);
	}
	else
	{
		m_renderer->SetTexture(0, m_textures[(int)DIR::BACK]);
		ResetUVDirection();
	}
}

Collider* SkullReplica::InitializeCollider(GameObject* colliderObj)
{
	colliderObj->transform->localScale = Vec3::one() * 1.25f;

    Collider* collider = colliderObj->AddComponent<SphereCollider>();
    collider->SetIgnoreLayerBits(1 << (uint8_t)PhysicsLayers::Monster);

	//{
	//	auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
	//	renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/transparent.png"));
	//	renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
	//}

    return collider;
}

void SkullReplica::OnDamage(DamageParameters& params)
{
    if (params.includeMonsterHitWorldPoint && params.includeDamageDirection)
    {
        GameObject* bloodEffectObj = CreateGameObject();
        bloodEffectObj->transform->position = params.monsterHitWorldPoint - params.damageDirection * 0.01f;
        bloodEffectObj->AddComponent<BloodEffect>();
    }
}

void SkullReplica::OnDead(bool& dead, DamageParameters& params)
{
	m_defaultEmissive = Color::black();
	m_defaultLightColor = Color::black();
}

void SkullReplica::SetLocalDistance(float value)
{
	transform->localPosition = m_initLocalDirection * value;
}

void SkullReplica::SetAttackTimer(float value)
{
	m_attackTimer = value;
}

void SkullReplica::SetAttackDelay(float value)
{
	m_attackDelay = value;
}

void SkullReplica::ChangeUVDirection(float angel)
{
    float direction = angel > 0 ? -1.0f : +1.0f;
    m_renderer->userMesh->uvScale = Vec2(direction, 1.0f);
}

void SkullReplica::ResetUVDirection()
{
    m_renderer->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
