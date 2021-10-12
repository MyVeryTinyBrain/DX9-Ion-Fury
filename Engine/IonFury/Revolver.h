#pragma once

#include "Weapon.h"

class Revolver : public Weapon
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual void OnChanged() override;

	virtual void OnAttackInput(InputType inputType) override;

	virtual void OnSubInput(InputType inputType) override;

	virtual void OnReloadInput(InputType inputType) override;

	void OnReloaded();

private:

	void TryReload();

	void Attack();

private:

	class RevolverAnimator* m_animator = nullptr;

	Vec2 m_rightHandLocalPositionTarget;

	Vec3 m_rightHandLocalEulerAngleTarget;
};

