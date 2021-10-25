#pragma once

#include "Monster.h"

class BasicMutantSpriteAnimator;

class BasicMutant :  public Monster
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

	void Attack();

	void ShootToPlayer();

	void OnDeadAnimated();

	void ColliderCheck();

	void AttackAfter();

private:

	UserMeshBillboardRenderer* m_renderer = nullptr;

	BasicMutantSpriteAnimator* m_animator = nullptr;

	bool m_hasTargetCoord = false;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	int m_attackCount = 0;

	float makePoisonDt = 0.f;

	bool create = true;

	float createdt = 0.f;

	float chageanimation = 0.f;

	bool SetAttack = true;

	bool SetIdle = false;

	bool  check = true;

	float idledt = 0.f;

	bool attack = false;

	int damage = 1;

	float pattern = 0.f;

	bool hittt = false;

	CapsuleCollider* m_CapsuleCollider = nullptr;

	float notPlayAttack = 0.f;

	bool hitdamage = false;;

	int AttackHp = 0;

	bool noAttack = false;
};

