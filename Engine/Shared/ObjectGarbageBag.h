#pragma once

#include "Monster.h"

class ObjectGarbageBag : public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	void OnCollisionEnter(const CollisionEnter& collision);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

	UserMeshRenderer* m_renderer = nullptr;

	Texture* m_texture[3] = {};

	float m_maxHP = 10.0f;
};

