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

	virtual AmmoTypes GetAmmoType0() const override;

	virtual AmmoTypes GetAmmoType1() const override;

	virtual unsigned int GetTotalAmmo0() const override;

	virtual unsigned int GetTotalAmmo1() const  override;

	virtual unsigned int GetLoadedAmmo0() const override;

	virtual unsigned int GetLoadedAmmo1() const override;

	virtual bool GetLoadedAmmo0State() const override;

	virtual bool GetLoadedAmmo1State() const override;

	virtual void AddAmmo(AmmoTypes ammo, unsigned int count) override;

	void OnRotateBarrel();

private:

	void RepositionBody();

	void MakeRightFireEffect();

	void Attack();

private:

	GameObject* m_bodyObj = nullptr;

	GameObject* m_bodyChildObj = nullptr;

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

	int m_ammo = 999;
};

