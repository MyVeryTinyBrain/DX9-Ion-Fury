#pragma once

#include "Weapon.h"

class Chaingun : public Weapon
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	virtual void OnChanged() override;

	virtual void OnPutIn() override;

	virtual void OnAttackInput(InputType inputType) override;

	virtual void OnSubInput(InputType inputType) override;

	virtual void OnReloadInput(InputType inputType) override;

	void OnRotateBarrel();

private:

	void MakeRightFireEffect();

	void Attack();

private:

	GameObject* m_bodyObj = nullptr;

	UserMeshRenderer* m_bodyRenderer = nullptr;

	GameObject* m_gunObj = nullptr;

	UserMeshRenderer* m_gunRenderer = nullptr;

	GameObject* m_ammoObj = nullptr;

	UserMeshRenderer* m_ammoRenderer = nullptr;

	class ChaingunGunpartAnimator* m_gunAnimator = nullptr;

	class ChaingunAmmopartAnimator* m_ammoAnimator = nullptr;

	float m_maxSpinSpeed = 20.0f;

	float m_spinFactor = 5.0f;

	bool m_hasAttackInput = false;

	int m_angleRange = 10;

	int m_ammo = 200;
};

