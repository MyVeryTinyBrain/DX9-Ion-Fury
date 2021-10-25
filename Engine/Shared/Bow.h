#pragma once

#include "Weapon.h"

class Bow : public Weapon
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

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

	void OnShoot();

	void OnReloaded();

private:

	void TryReload();

	void Attack();

	void SetScreen(int value);

	void MakeFireEffect();

private:

	GameObject* m_bodyObj = nullptr;

	GameObject* m_bowObj = nullptr;

	UserMeshRenderer* m_bowRenderer = nullptr;

	class BowAnimator* m_bowAnimator = nullptr;

	GameObject* m_stringEffectObj = nullptr;

	UserMeshRenderer* m_stringEffectRenderer = nullptr;

	class BowStringAnimator* m_stringEffectAnimator = nullptr;

	GameObject* m_screenObj = nullptr;

	UserMeshRenderer* m_screenRenderer = nullptr;

	Texture* m_screenTexture[6] = {};

	int m_totalAmmo = 100;

	int m_loadedAmmo = 5;

	int m_ammoLoadMax = 5;

	float m_shootDelay = 0.7f;

	float m_shootCounter = 0.0f;
};

