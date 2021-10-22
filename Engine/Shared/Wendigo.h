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


private:

	enum class ActionType { Idle, Walk , Jump, Swing, Max};

	enum class AttackType { Jump, Swing, Max};

	void Moving(ActionType type);

private:

	void Jump();

	void SetTargetCoord(Vec3 xzCoord);

	void AttackToPlayer();

	void JumpCheck();

	void MoveToTarget();
	
private:

	CapsuleCollider* m_capsuleCollider = nullptr;

	WendigoSpriteAnimator* m_animator = nullptr;

	UserMeshBillboardRenderer* m_renderer = nullptr;

	bool m_hasTargetCoord = false;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	bool m_hasJump = false;

	ActionType actionType = ActionType::Idle;

	AttackType attackType = AttackType::Max;

	bool m_initialPos = true;

	Vec3 m_forward;

	float m_jumpY = 0.f;

	bool m_jump = true;

	float m_jumptime = 0.f;

	float m_PatternTime = 0;
};

