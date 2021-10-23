#pragma once

#include "Monster.h"

class WendigoSpriteAnimator;

class Wendigo : public Monster
{
	enum class Behavior { MoveToPlayer, Jump, Swing, WalkToRandomCoord,  RandomMax, Idle,  None };

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

	void OnPlayedJump();

	void OnPlayedSwing();

	void OnPlayedAttack();

	void OnPlayedDie();

private:

	void SetBehavior(Behavior value);

	void BehaviorUpdate();

	void OnIdle();

	void Idle();

	void OnMoveToPlayer();

	void MoveToPlayer();

	void OnJump();

	void OnSwing();

	void OnWalkToRandomCoord();

	void Swing();

	void WalkToRandomCoord();

private:

	void MoveToTarget();

	void SetTargetCoord(Vec3 xzCoord);

	void Jump();

	void JumpCheck();

private:


	enum class ActionType { Idle, WalkToRandomCoord, WalkToPlayerDirection, Swing, Jump, Max };

	enum class AttackType { Swing, Jump, Max };

	void SetAction(ActionType type);

	void AttackToPlayer();

	void Attack();

private:

	UserMeshBillboardRenderer* m_renderer = nullptr;

	CapsuleCollider* m_capsuleCollider = nullptr;

	WendigoSpriteAnimator* m_animator = nullptr;

	bool m_hasTargetCoord = false;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	float m_breakTime = 0.f;

	unsigned int m_attackCount = 0;

	ActionType actionType = ActionType::Max;

	bool m_attacking = false;

	bool m_hasJump = false;

	float m_jumpY = 0.f;

	bool m_jump = true;

	float m_jumptime = 0.f;

	float m_deadTime = 0.f;

	AttackType attackType = AttackType::Max;

	bool m_initialdir = true;

	Vec3 forward;

	Behavior m_behavior = Behavior::None;

	float m_idleAccumulate = 0.0f;

	float m_moveToPlayerAccumulate = 0.0f;
};

