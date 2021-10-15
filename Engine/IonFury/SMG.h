#pragma once

#include "Weapon.h"

class SMG : public Weapon
{
	struct Ammo
	{
		int totalAmmo = 100;
		int loadedAmmo = 30;
		int ammoLoadMax = 30;
	};

private:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnChanged() override;

	virtual void OnAttackInput(InputType inputType) override;

	virtual void OnSubInput(InputType inputType) override;

	virtual void OnReloadInput(InputType inputType) override;

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

private:

	Ammo m_leftAmmo;

	Ammo m_rightAmmo;

	GameObject* m_hansParentObj = nullptr;

	GameObject* m_rightHandObj = nullptr;

	UserMeshRenderer* m_rightHandRenderer = nullptr;

	class SMGAnimator* m_rightHandAnimator = nullptr;

	GameObject* m_leftHandObj = nullptr;

	GameObject* m_leftHandChild = nullptr;

	UserMeshRenderer* m_leftHandRenderer = nullptr;

	class SMGAnimator* m_leftHandAnimator = nullptr;

	QuadUserMesh* m_leftHandQuad = nullptr;

};

