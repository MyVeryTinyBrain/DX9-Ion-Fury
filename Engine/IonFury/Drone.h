#pragma once

#include "Monster.h"

class DroneSpriteAnimator;

class Drone :  public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force) override;

	virtual void OnDead(bool& dead, MonsterDamageType damageType) override;

private:


	void SetTargetCoord(Vec3 xzCoord);

	void Attack();

	void FindTarget();

private:

	enum class MovingType { Idle, Trace, leftRight, Attack, Max };

	void Moving(MovingType type);

private:
	
	DroneSpriteAnimator* m_animator = nullptr;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	bool m_hasTargetCoord = false;

	float m_deltatime = 0.f;

	unsigned int m_attackCount = 0;

	bool m_distance = false;

	float m_breakTime = 0;
};

