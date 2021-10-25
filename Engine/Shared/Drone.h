#pragma once

#include "Monster.h"

class DroneSpriteAnimator;

class Drone : public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

private:

	void SetTargetCoord(Vec3 xzCoord);

	void Attack();

	void Explosion();

	void ShootToPlayer();

	void DistanceCheck();

private:

	enum class MovingType { Idle, Trace, leftRight, Attack, Max };

	void Moving(MovingType type);

private:

	UserMeshBillboardRenderer* m_renderer = nullptr;

	DroneSpriteAnimator* m_animator = nullptr;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	bool m_hasTargetCoord = false;

	float m_deltatime = 0.f;

	unsigned int m_attackCount = 0;

	bool m_distance = false;

	float m_breakTime = 0;

	MovingType movingtype = (MovingType)0;

	bool m_damageToPlayer = false;

	float m_movingTime = 0.f;

	MovingType Premovingtype = MovingType::Max;

	float m_attackTimer = 0;

};
