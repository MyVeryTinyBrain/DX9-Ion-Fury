#pragma once

#include "Monster.h"

class SpiderSpriteAnimator;

class Web : public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force) override;

	virtual void OnDead(bool& dead, MonsterDamageType damageType) override;

private:

	SpiderSpriteAnimator* m_animator = nullptr;

	float m_animationtime = 0;
};

