#pragma once
#include "Monster.h"

class DeaconSpriteAnimator;

class Deacon : public Monster
{
	enum class Behavior { MoveToPlayer, ShootBall, RandomMax, Idle, Landing, None };
	//enum class Behavior { MoveToPlayer, FlyToPlayer, ShootBall, RandomMax, Idle, Landing, None };
	//enum class Behavior { MoveToPlayer , RandomMax, FlyToPlayer, ShootBall, Idle, Landing, None };

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

	//void OnPlayedFly();

	//void OnPlayedLand();

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

	void OnMoveToPlayer();

	void MoveToPlayer();

//	void OnFlyToPlayer();

//	void FlyToPlayer();

//	void OnLanding();

//	void Landing();

	void OnShootBall();

	void ShootBall();

	void ShootToPlayer();

private:

	UserMeshRenderer* m_renderer = nullptr;

	CapsuleCollider* m_collider = nullptr;

	CapsuleUserMesh* m_colliderDebugMesh = nullptr;

	UserMeshRenderer* m_colliderDebugRenderer = nullptr;

	DeaconSpriteAnimator* m_animator = nullptr;

	Behavior m_behavior = Behavior::None;

	float m_idleAccumulate = 0.0f;

	float m_shootWait = 0.0f;

	int m_shootCount = 0;

	float m_moveToPlayerAccumulate = 0.0f;

	float createEffect = 0.f;
};

