#include "stdafx.h"
#include "Web.h"
#include "Player.h"
#include "SpiderSpriteAnimator.h"

void Web::Awake()
{
	Monster::Awake();

	m_moveSpeed = 2.0f;

	m_body->mass = 0.01f;
	m_body->interpolate = true;


	m_rendererObj->transform->scale = Vec3::one() * 4.0f;
	m_rendererObj->transform->localPosition = Vec3(0, -0.5, 0);

	m_animator = m_rendererChildObj->AddComponent<SpiderSpriteAnimator>();
}

void Web::Update()
{
	Monster::Update();

	m_animationtime += Time::DeltaTime();

	if (m_animationtime < 0.4f)
	{
		m_animator->SetDefaultAnimation(m_animator->GetWeb(), true);
		
		
		m_body->isKinematic = true;

		m_collider->friction = 1.0f;

		Vec3 velocity = transform->forward * m_moveSpeed;
		//m_body->velocity = velocity;

		transform->position += transform->forward * m_moveSpeed * Time::DeltaTime();
	}
	else
	{
		m_animator->Pause();
	}


}

void Web::LateUpdate()
{
	Monster::LateUpdate();

	if (m_animationtime > 3.f)
		Destroy();
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
