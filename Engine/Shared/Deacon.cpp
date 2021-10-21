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

    gameObject->transform->scale = Vec3::one() * 5.f;

    m_hp = 30;
    m_moveSpeed = 3.f;

    m_body->mass = 3.f;
    m_body->interpolate = Interpolate::Extrapolate;
    m_body->sleepThresholder = 2.0f;

   // m_rendererObj->transform->localScale 
}

void Deacon::FixedUpdate()
{
    Monster::FixedUpdate();

    if (Time::FixedTimeScale() == 0)
        return;
}

void Deacon::Update()
{
    Monster::Update();

    if (Time::TimeScale() == 0)
        return;
}

void Deacon::LateUpdate()
{
    Monster::LateUpdate();

    if (Time::TimeScale() == 0)
        return;
}

void Deacon::OnDestroy()
{
    Monster::OnDestroy();

    if (Time::TimeScale() == 0)
        return;
}

Collider* Deacon::InitializeCollider(GameObject* colliderObj)
{
    return nullptr;
}

void Deacon::OnDamage(DamageParameters& params)
{
}

void Deacon::OnDead(bool& dead, DamageParameters& params)
{
}

void Deacon::OnPlayedFly()
{
}

void Deacon::OnPlayedLand()
{
}

void Deacon::OnPlayedAttack()
{
}

void Deacon::OnPlayedDie()
{
}

float Deacon::GetXZDistance(const Vec3& point) const
{
    return 0.0f;
}

Vec3 Deacon::GetXZDirection(const Vec3& point) const
{
    return Vec3();
}

bool Deacon::WallTest(const Vec3& direction) const
{
    return false;
}

void Deacon::MakeFlyEffect()
{
}

void Deacon::SetBehavior(Behavior value)
{
}

void Deacon::BehaviorUpdate()
{
}

void Deacon::OnIdle()
{
}

void Deacon::Idle()
{
}

void Deacon::OnFlyToPlayer()
{
}

void Deacon::FlyToPlayer()
{
}

void Deacon::OnLanding()
{
}

void Deacon::Landing()
{
}

void Deacon::OnShootBall()
{
}

void Deacon::ShootBall()
{
}
