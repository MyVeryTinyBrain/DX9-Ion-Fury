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

	// 플레이어에게 레이를 발사해 장애물이 있는지 확인합니다.
	bool PlayerInSite() const;

	// 1. 목표 지점으로 방향을 틉니다.
	// 2. 목표 지점으로 향하는 속도를 설정합니다.
	void MoveToTarget();

	// 이동할 위치를 설정합니다.
	// y = 0 으로 설정됩니다.
	void SetTargetCoord(Vec3 xzCoord);

private:

	GunnerSpriteAnimator* m_animator = nullptr;

	bool m_hasTargetCoord = false;

	// y = 0으로 설정됩니다.
	Vec3 m_targetCoord;
};

