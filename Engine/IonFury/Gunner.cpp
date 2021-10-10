#include "stdafx.h"
#include "Gunner.h"
#include "GunnerSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"

void Gunner::Awake()
{
    Monster::Awake();

    m_hp = 10;
    m_moveSpeed = 4.0f;

    m_body->mass = 1.0f;
    m_body->interpolate = true;

    m_rendererObj->transform->scale = Vec3::one() * 3.0f;
    m_animator = m_rendererChildObj->AddComponent<GunnerSpriteAnimator>();

    SetTargetCoord(Vec3(0, 0, -5));
}

void Gunner::FixedUpdate()
{
    Monster::FixedUpdate();

    MoveToTarget();
    m_animator->SetAngle(AngleToPlayerWithSign());
}

void Gunner::Update()
{
    Monster::Update();

    //MoveToTarget();
    //m_animator->SetAngle(AngleToPlayerWithSign());
}

void Gunner::OnDestroy()
{
    Monster::OnDestroy();
}

Collider* Gunner::InitializeCollider(GameObject* colliderObj)
{
    //{
    //    auto renderer = colliderObj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/transparent.png"));
    //    renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);
    //}

    return colliderObj->AddComponent<CapsuleCollider>();
}

void Gunner::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
    switch (damageType)
    {
        case MonsterDamageType::Bullet:
        case MonsterDamageType::Explosion:
            m_animator->PlayDamage(GunnerSpriteAnimator::DAMAGE::DAMAGE_GENERIC);
            break;
        case MonsterDamageType::Zizizik:
            m_animator->PlayDamage(GunnerSpriteAnimator::DAMAGE::DAMAGE_ZIZIZIK);
            break;
    }

	const Vec3& playerPos = Player::GetInstance()->transform->position;
	const Vec3& gunnerPos = transform->position;
    Vec3 forward = playerPos - gunnerPos;
    forward.y = 0;
    forward.Normalize();
    transform->forward = forward;
}

void Gunner::OnDead(bool& dead, MonsterDamageType damageType)
{
}

bool Gunner::PlayerInSite() const
{
    return false;
}

void Gunner::MoveToTarget()
{
    if (!m_hasTargetCoord)
    {
        return;
    }

    const Vec3& gunnerPos = transform->position;
    Vec3 forward = m_targetCoord - gunnerPos;
    forward.y = 0;
    forward.Normalize();
    transform->forward = forward;

    Vec3 xzGunnerPos = Vec3(gunnerPos.x, 0, gunnerPos.z);
    float distance = Vec3::Distance(xzGunnerPos, m_targetCoord);

    if (distance > 2.1f)
    {
        Vec3 acceleration = forward * m_moveSpeed;
        Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
        velocity.y = m_body->velocity.y;
        m_body->velocity = velocity;

        //Vec3 acceleration = forward * m_moveSpeed;
        //Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
        //velocity.y = 0;
        //transform->position += velocity * Time::DeltaTime();
    }
    else
    {
        m_hasTargetCoord = false;

        float randomAngle = float(rand() % 360);
        Vec3 randomDir = Vec3(cosf(randomAngle * Deg2Rad), 0, sinf(randomAngle * Deg2Rad));
        float randomDist = float(rand() % 10 + 1);
        SetTargetCoord(transform->position + randomDir * randomDist);
    }
}

void Gunner::SetTargetCoord(Vec3 xzCoord)
{
    m_hasTargetCoord = true;
    m_targetCoord = xzCoord;
    m_targetCoord.y = 0;
}
