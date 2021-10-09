#include "stdafx.h"
#include "Gunner.h"
#include "GunnerSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"

void Gunner::Awake()
{
    Monster::Awake();

    m_hp = 10;
    m_moveSpeed = 5.0f;

    m_body->mass = 5.0f;

    m_rendererObj->transform->scale = Vec3::one() * 3.0f;
    m_animator = m_rendererChildObj->AddComponent<GunnerSpriteAnimator>();
}

void Gunner::FixedUpdate()
{
    Monster::FixedUpdate();

	//const Vec3& playerPos = Player::GetInstance()->transform->position;
	//const Vec3& gunnerPos = transform->position;
	//Vec3 gunnerToPlayer = playerPos - gunnerPos;
	//gunnerToPlayer.Normalize();

	//Vec3 acceleration = gunnerToPlayer * m_moveSpeed;
	//Vec3 velocity = ToSlopeVelocity(acceleration, sqrtf(2.0f));
	//velocity.y = m_body->velocity.y;
	//m_body->velocity = velocity;
}

void Gunner::Update()
{
    Monster::Update();

    const Vec3& playerPos = Player::GetInstance()->transform->position;
    const Vec3& gunnerPos = transform->position;
    Vec3 gunnerToPlayer = playerPos - gunnerPos;
    float distance = gunnerToPlayer.magnitude();
    gunnerToPlayer.Normalize();

    if (distance > 2)
    {
        gunnerToPlayer.y = 0;
        transform->position += gunnerToPlayer * m_moveSpeed * Time::DeltaTime();
    }

    m_animator->PlayWalk(GunnerSpriteAnimator::DIR::FRONT);
}

void Gunner::OnDestroy()
{
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
}

void Gunner::OnDead(bool& dead, MonsterDamageType damageType)
{
}
