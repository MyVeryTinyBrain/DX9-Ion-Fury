#pragma once

#include "Monster.h"

class SkullReplica : public Monster
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(LateUpdate);

	virtual Collider* InitializeCollider(GameObject* colliderObj) override;

	virtual void OnDamage(DamageParameters& params) override;

	virtual void OnDead(bool& dead, DamageParameters& params) override;

public:

	void SetLocalDistance(float value);

	void SetAttackTimer(float value);

	void SetAttackDelay(float value);

private:

	void ChangeUVDirection(float angle);

	void ResetUVDirection();

private:

	enum class DIR { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	Vec3 m_initLocalDirection = Vec3::zero();

	Texture* m_textures[(int)DIR::MAX] = {};

	UserMeshBillboardRenderer* m_renderer = nullptr;

	float m_attackDelay = 0.2f;

	float m_attackTimer = m_attackDelay;
};

