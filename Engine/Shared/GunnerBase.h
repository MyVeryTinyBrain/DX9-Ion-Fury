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

	// �÷��̾�� ���̸� �߻��� ��ֹ��� �ִ��� Ȯ���մϴ�.
	bool IsPlayerInSite(Vec3& playerCoord);

	// 1. ��ǥ �������� ������ Ƶ�ϴ�.
	// 2. ��ǥ �������� ���ϴ� �ӵ��� �����մϴ�.
	void MoveToTarget();

	// �̵��� ��ġ�� �����մϴ�.
	// y = 0 ���� �����˴ϴ�.
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

	// ��ǥ ������ �ִ� ��쿡 Ȱ��ȭ�Ǵ� �÷����Դϴ�.
	bool m_hasTargetCoord = false;

	// y = 0���� �����˴ϴ�.
	Vec3 m_targetCoord;

	// y = 0���� �����˴ϴ�.
	Vec3 m_beforeCoord;

	// ������ ��� �����ϴµ� ���̴� Ÿ�̸��Դϴ�.
	float m_breakTime = 0;

	// ������ �� �� ī���Ͱ� 0���� ũ�ٸ� ī���͸� 1 ���ҽ�Ű�� ������ �մϴ�.
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

