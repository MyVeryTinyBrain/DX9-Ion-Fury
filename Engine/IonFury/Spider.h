#pragma once

#include "Monster.h"

class SpiderSpriteAnimator;

class Spider : public Monster
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

	void JumpCheck();

	void Jump();

private:

	enum class JumpType { BASIC, WEB, MAX };

private:

	UserMeshBillboardRenderer* m_renderer = nullptr;

	SpiderSpriteAnimator* m_animator = nullptr;
	
	bool m_hasTargetCoord = false;

	Vec3 m_targetCoord;

	Vec3 m_beforeCoord;

	float m_jumpSpeed = 5.0f;

	bool m_hasJump = false;

	unsigned int m_attackCount = 0;

	float m_jumpY = 0.f;

	bool m_jump = true;

	float m_jumptime = 0.f;

	bool m_attack = true;

	float m_PatternTime = 0;

	JumpType jumpingtype = (JumpType)0;
};

