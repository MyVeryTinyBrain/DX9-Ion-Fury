#pragma once

#include "Weapon.h"

class Revolver : public Weapon
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual void OnChanged() override;

	virtual void OnPutIn() override;

	virtual void OnAttackInput(InputType inputType) override;

	virtual void OnSubInput(InputType inputType) override;

	virtual void OnReloadInput(InputType inputType) override;

	void OnReloaded();

private:

	void TryReload();

	void Attack();

	void MakeFireEffect();

private:

	GameObject* m_rightHandObj = nullptr;

	UserMeshRenderer* m_rightHandRenderer = nullptr;

	class RevolverAnimator* m_animator = nullptr;

	Vec2 m_rightHandLocalPositionTarget;

	Vec3 m_rightHandLocalEulerAngleTarget;

	GameObject* m_leftHandObj = nullptr;

	GameObject* m_leftHandChildObj = nullptr;

	UserMeshRenderer* m_leftHandRenderer = nullptr;

	Vec2 m_leftHandLocalPositionTarget;

	const Vec2 m_leftHandHideLocalPosition = Vec2(0, -0.45f);

	const Vec2 m_leftHandShowLocalPosition = Vec2(0.6f, -0.1f);

	const int m_rapidFireRecoilAngleRange = 40;

	int m_totalAmmo = 100;

	int m_loadedAmmo = 6;

	int m_ammoLoadMax = 6;
};

