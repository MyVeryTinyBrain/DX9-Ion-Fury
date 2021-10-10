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

	virtual void OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force) override;

	virtual void OnDead(bool& dead, MonsterDamageType damageType) override;

private:

	// �÷��̾�� ���̸� �߻��� ��ֹ��� �ִ��� Ȯ���մϴ�.
	bool PlayerInSite() const;

	// 1. ��ǥ �������� ������ Ƶ�ϴ�.
	// 2. ��ǥ �������� ���ϴ� �ӵ��� �����մϴ�.
	void MoveToTarget();

	// �̵��� ��ġ�� �����մϴ�.
	// y = 0 ���� �����˴ϴ�.
	void SetTargetCoord(Vec3 xzCoord);

private:

	GunnerSpriteAnimator* m_animator = nullptr;

	bool m_hasTargetCoord = false;

	// y = 0���� �����˴ϴ�.
	Vec3 m_targetCoord;
};

