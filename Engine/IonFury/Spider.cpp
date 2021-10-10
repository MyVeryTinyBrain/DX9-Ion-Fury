#include "stdafx.h"
#include "Spider.h"
#include "SpiderSpriteAnimator.h"
#include "Player.h"
#include "PhysicsLayers.h"

void Spider::Awake()
{
    Monster::Awake();


}

void Spider::FixedUpdate()
{
    Monster::FixedUpdate();

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
    return nullptr;
}

void Spider::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
}

void Spider::OnDead(bool& dead, MonsterDamageType damageType)
{
}
