#pragma once

#include "Weapon.h"

class SMG : public Weapon
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

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

	void OnPlayedLeftPutin();

	void OnPlayLeftPullout();

	void OnRightReloaded();

	void OnLeftReloaded();

private:

	void TryReload();

	void AttackOnce(int recoilAngleRange);

private:

	void MakeRightFireEffect();

	void MakeLeftFireEffect();

	void DebugAmmos();

private:

	int m_totalAmmo = 300;

	int m_ammoLoadMax = 30;

	int m_leftAmmo = 30;

	int m_rightAmmo = 30;

	GameObject* m_hansParentObj = nullptr;

	GameObject* m_rightHandObj = nullptr;

	UserMeshRenderer* m_rightHandRenderer = nullptr;

	class SMGAnimator* m_rightHandAnimator = nullptr;

	GameObject* m_leftHandObj = nullptr;

	GameObject* m_leftHandChild = nullptr;

	UserMeshRenderer* m_leftHandRenderer = nullptr;

	class SMGAnimator* m_leftHandAnimator = nullptr;

	QuadUserMesh* m_leftHandQuad = nullptr;

	int m_lastChannelIndex = 0;

};

