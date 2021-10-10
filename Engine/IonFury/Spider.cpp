#include "stdafx.h"
#include "Spider.h"
#include "SpiderSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"

void Spider::Awake()
{
    Monster::Awake();

    m_hp = 5;
    m_moveSpeed = 4.0f;

    m_body->mass = 0.5f;
    m_body->interpolate = true;

    m_rendererObj->transform->scale = Vec3::one() * 3.0f;
    m_rendererObj->transform->localPosition = Vec3(0, -0.5, 0);
    m_animator = m_rendererChildObj->AddComponent<SpiderSpriteAnimator>();

    //SetTargetCoord(Vec3(0, 0, -5));
    SetTargetCoord(Player::GetInstance()->transform->position);
}

void Spider::FixedUpdate()
{
    Monster::FixedUpdate();
   // MoveToTarget();
    
}

void Spider::Update()
{
    Monster::Update();

}

void Spider::OnDestroy()
{
    Monster::OnDestroy();

}

Collider* Spider::InitializeCollider(GameObject* colliderObj)
{
    return colliderObj->AddComponent<SphereCollider>();
}

void Spider::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
}

void Spider::OnDead(bool& dead, MonsterDamageType damageType)
{
}

void Spider::MoveToTarget()
{
    if (!m_hasTargetCoord)
        return;

    const Vec3& spiderPos = transform->position;
    Vec3 forward = m_targetCoord - spiderPos;
    forward.y = 0; 
    forward.normalized();
    transform->forward = forward;

    Vec3 xzSpiderPos = Vec3(spiderPos.x, 0, spiderPos.z);
    float distance = Vec3::Distance(xzSpiderPos, m_targetCoord);

    if(distance > 2.1f)
    {

    }
    else
    {
        m_hasTargetCoord = false;
    }
}

void Spider::SetTargetCoord(Vec3 xzCoord)
{
    m_hasTargetCoord = true;
    m_targetCoord = xzCoord;
    m_targetCoord.y = 0;
}
