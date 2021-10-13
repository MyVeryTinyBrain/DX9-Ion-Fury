#include "stdafx.h"
#include "Web.h"
#include "Player.h"
#include "SpiderSpriteAnimator.h"

void Web::Awake()
{
	Monster::Awake();

	m_moveSpeed = 2.0f;

	m_body->mass = 0.5f;
	m_body->interpolate = true;

	m_rendererObj->transform->scale = Vec3::one() * 3.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -0.5, 0);

	m_animator = m_rendererChildObj->AddComponent<SpiderSpriteAnimator>();
}

void Web::Update()
{
	Monster::Update();


	Vec3 playerPos = Player::GetInstance()->transform->position;
	Vec3 webPos = transform->position;
	Vec3 forward = playerPos - webPos;
	forward.Normalize();

	Vec3 velocity = forward * m_moveSpeed;
	velocity.y = 0;
	m_body->velocity = velocity;

	//transform->position += forward * 0.03f;

	m_animator->PlayWeb();
}

void Web::OnDestroy()
{
	Monster::OnDestroy();
}

Collider* Web::InitializeCollider(GameObject* colliderObj)
{
    return colliderObj->AddComponent<BoxCollider>();
}

void Web::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
}

void Web::OnDead(bool& dead, MonsterDamageType damageType)
{
}
