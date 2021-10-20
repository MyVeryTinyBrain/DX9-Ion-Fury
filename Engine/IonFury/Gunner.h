#pragma once

#include "Monster.h"

class GunnerSpriteAnimator;

class Gunner : public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

	void OnDeadAnimated();

private:

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

	void ShootToPlayer();

private:

	UserMeshBillboardRenderer* m_renderer = nullptr;

	CapsuleCollider* m_capsuleCollider = nullptr;

	GunnerSpriteAnimator* m_animator = nullptr;

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
};

