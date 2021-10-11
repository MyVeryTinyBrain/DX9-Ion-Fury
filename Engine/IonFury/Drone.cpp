#include "stdafx.h"
#include "Drone.h"

void Drone::Awake()
{
}

void Drone::FixedUpdate()
{
}

void Drone::Update()
{
}

void Drone::OnDestroy()
{
}

Collider* Drone::InitializeCollider(GameObject* colliderObj)
{
	return nullptr;
}

void Drone::OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force)
{
}

void Drone::OnDead(bool& dead, MonsterDamageType damageType)
{
}
