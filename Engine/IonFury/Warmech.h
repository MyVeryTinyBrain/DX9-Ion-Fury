#pragma once

#include "Monster.h"

class WarmechSpriteAnimator;

class Warmech : public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

private:

	void MoveToTarget();

	void SetTargetCoord(Vec3 xzCoord);

	void Explosion();

private:

	enum class ActionType { Idle, WalkToRandomCoord, WalkToPlayerDirection, Attack, Max };

	enum class AttackType { Bullet, Missile, Max };

	void SetAction(ActionType type, AttackType attacktype);

	void Attack(AttackType type);

private:

	CapsuleCollider* m_capsuleCollider = nullptr;

	WarmechSpriteAnimator* m_bodyAnimator = nullptr;

	WarmechSpriteAnimator* m_legAnimator = nullptr;

	GameObject* m_bodyWarmech = nullptr;

	GameObject* m_legWarmech = nullptr;

	bool m_hasTargetCoord = false;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	float m_breakTime = 0;

	unsigned int m_attackCount = 0;
};

