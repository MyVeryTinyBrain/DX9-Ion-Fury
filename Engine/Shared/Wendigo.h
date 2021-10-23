#pragma once

#include "Monster.h"

class WendigoSpriteAnimator;

class Wendigo : public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

	void OnCollisionEnter(const CollisionEnter& collider);

private:

	void MoveToTarget();

	void SetTargetCoord(Vec3 xzCoord);

	void Jump();

	void JumpCheck();

	void TerrainCheck();

private:


	enum class ActionType { Idle, WalkToPlayerDirection, Swing, Jump, Max };

	enum class AttackType { Swing, Jump, Max };

	void SetAction(ActionType type);

private:

	UserMeshBillboardRenderer* m_renderer = nullptr;

	CapsuleCollider* m_capsuleCollider = nullptr;

	WendigoSpriteAnimator* m_animator = nullptr;

	bool m_hasTargetCoord = false;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	unsigned int m_attackCount = 0;

	ActionType actionType = ActionType::Max;

	bool m_hasJump = false;

	float m_jumpY = 0.f;

	bool m_jump = true;

	float m_jumptime = 0.f;

	AttackType attackType = AttackType::Max;

	Vec3 m_forward;

	float m_PatternTime = 0;

};

