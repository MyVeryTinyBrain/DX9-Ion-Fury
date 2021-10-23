#pragma once
#include "Monster.h"

class DeaconSpriteAnimator;

class Deacon : public Monster
{
	enum class Behavior {FlyToPlayer, ShootBall, RandomMax, Idle, Landing, None };

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

	void OnPlayedFly();

	void OnPlayedLand();

	void OnPlayedAttack();

	void OnPlayedDie();

private:

	float GetXZDistance(const Vec3& point) const;

	Vec3 GetXZDirection(const Vec3& point) const;

	bool WallTest(const Vec3& direction) const;

	void MakeFlyEffect();

private:

	void SetBehavior(Behavior value);

	void BehaviorUpdate();

	void OnIdle();

	void Idle();

	void OnFlyToPlayer();

	void FlyToPlayer();

	void OnLanding();

	void Landing();

	void OnShootBall();

	void ShootBall();

private:


	SphereCollider* m_collider = nullptr;

	class DeaconAnimator* m_animator = nullptr;

	Behavior m_behavior = Behavior::None;

	float m_idleAccumulate = 0.0f;

	float m_shootWait = 0.0f;

	int m_shootCount = 0;
};

