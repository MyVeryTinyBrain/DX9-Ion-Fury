#pragma once

#include "Monster.h"

class Skull : public Monster
{
	enum class Behavior { MoveToPlayer, FlyToPlayer, ShootBall, FlyReplica, RandomMax, Idle, Landing, EndReplica, None };

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

	void OnMoveToPlayer();

	void MoveToPlayer();

	void OnFlyToPlayer();

	void FlyToPlayer();

	void OnLanding();

	void Landing();

	void OnShootBall();

	void ShootBall();

	void OnFlyReplica();

	void FlyReplica();

	void OnEndReplica();

	void EndReplica();

private:

	enum { REPLICA_MAX = 6 };

	CapsuleCollider* m_collider = nullptr;

	CapsuleUserMesh* m_colliderDebugMesh = nullptr;

	UserMeshRenderer* m_colliderDebugRenderer = nullptr;

	UserMeshRenderer* m_renderer = nullptr;

	class SkullAnimator* m_animator = nullptr;

	float m_flyEffectCounter = 0;

	Behavior m_behavior = Behavior::None;

	float m_idleAccumulate = 0.0f;

	float m_moveToPlayerAccumulate = 0.0f;

	//Vec3 m_flyTarget;

	float m_shootWait = 0.0f;

	int m_shootCount = 0;

	GameObject* m_replicaRoot = nullptr;

	bool m_hasReplicas = false;

	float m_replicaLocalDistance = 0.0f;

	Ref<class SkullReplica> m_replicas[REPLICA_MAX];
};

