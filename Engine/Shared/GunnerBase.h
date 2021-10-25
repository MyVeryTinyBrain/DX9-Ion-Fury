#pragma once

#include "Monster.h"
#include "IMonsterSpawn.h"

class GunnerBaseAnimator;

class GunnerBase : public Monster, public IMonsterSpawn
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	OverrideComponentFunction(OnWake);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

	void OnDeadAnimated();

	virtual void OnSpawn();

protected:

	virtual GunnerBaseAnimator* InitAnimator(GameObject* rendererObject) = 0;

	virtual unsigned int GetAttackCount() = 0;

	virtual float GetDamagedRevengeAttackWaitTime() = 0;

	virtual float GetBreakTime() = 0;

	virtual float GetAttackWaitTime() = 0;

	virtual void ShootToPlayer() = 0;

protected:

	// 플레이어에게 레이를 발사해 장애물이 있는지 확인합니다.
	bool IsPlayerInSite(Vec3& playerCoord);

	// 1. 목표 지점으로 방향을 틉니다.
	// 2. 목표 지점으로 향하는 속도를 설정합니다.
	void MoveToTarget();

	// 이동할 위치를 설정합니다.
	// y = 0 으로 설정됩니다.
	void SetTargetCoord(Vec3 xzCoord);

	void Attack();

private:

	enum class BehaviorType
	{
		Idle, WalkToRandomCoord, WalkToPlayerDirection, Attack, Max
	};

	void SetBehavior(BehaviorType type);

protected:

	UserMeshBillboardRenderer* m_renderer = nullptr;

	CapsuleCollider* m_capsuleCollider = nullptr;

	GunnerBaseAnimator* m_animator = nullptr;

	// 목표 지점이 있는 경우에 활성화되는 플래그입니다.
	bool m_hasTargetCoord = false;

	// y = 0으로 설정됩니다.
	Vec3 m_targetCoord;

	// y = 0으로 설정됩니다.
	Vec3 m_beforeCoord;

	// 동작을 잠시 정지하는데 쓰이는 타이머입니다.
	float m_breakTime = 0;

	// 공격할 때 이 카운터가 0보다 크다면 카운터를 1 감소시키고 공격을 합니다.
	unsigned int m_attackCount = 0;

	float m_attackWaitCounter = 0;

	BehaviorType m_behavior = BehaviorType::Idle;

	bool m_holdPosition = false;

protected:

	enum { HURT_SOUND_MAX = 3, DEATH_SOUND_MAX = 2, GUN_SOUND_MAX = 7 };

	static int g_hurtSoundIndex;

	static int g_deathSoundIndex;

	static int g_gunSoundIndex;
};

