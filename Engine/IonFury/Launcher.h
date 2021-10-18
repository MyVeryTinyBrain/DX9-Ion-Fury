#pragma once

#include "Weapon.h"

class Launcher : public Weapon
{
	enum class Mode
	{
		Shotgun, Launcher
	};

	struct Ammo
	{
		int totalAmmo = 100;
		int loadedAmmo = 6;
		int ammoLoadMax = 6;
	};

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

	void OnReloaded();

	void OnSkinChanged();

private:

	void TryReload();

	void Attack();

	void AttackWithShotgun();

	void AttackWithLauncher();

	void ShotgunShootOnce();

	void LauncherShootOnce();

	void MakeFireEffect();

private:

	GameObject* m_rightHandObj = nullptr;

	UserMeshRenderer* m_rightHandRenderer = nullptr;

	class LauncherAnimator* m_animator = nullptr;

	const Vec2 m_rightHandLocalScale = Vec2(2, 2);

	const Vec2 m_rightHandLocalPosition = Vec2(-0.4f, 0.4f);

	Mode m_mode = Mode::Shotgun;

	const int m_shotgunSpreadAngleRange = 40;

	const int m_numShotgunBullet = 20;

	Ammo m_shotgunAmmo;

	Ammo m_launcherAmmo;

	Ammo* m_currentAmmo = nullptr;
};

