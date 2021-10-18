#pragma once

#include "AmmoTypes.h"

class Numbers;

class PlayerUI : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	void ShowRedScreenEffect();

	void ShowGreenScreenEffect();

	void ShowBlueScreenEffect();

	void SetHP(unsigned int value);

	void SetLoadedAmmo0State(bool value);

	void SetLoadedAmmo1State(bool value);

	void SetLoadedAmmo0(unsigned int value);

	void SetLoadedAmmo1(unsigned int value);

	void SetAmmo0(unsigned int value);

	void SetAmmo1(unsigned int value);

	void SetAmmo0Type(AmmoTypes type);

	void SetAmmo1Type(AmmoTypes type);

private:

	GameObject* m_playerFaceObj = nullptr;

	UserMeshRenderer* m_playerFaceRenderer = nullptr;

	Texture* m_playerFaceTexture[4] = {};

	GameObject* m_hpObj = nullptr;

	Numbers* m_hpNumbers = nullptr;

	GameObject* m_ammoObj0 = nullptr;

	Numbers* m_ammoNumbers0 = nullptr;

	GameObject* m_loadedAmmoObj0 = nullptr;

	Numbers* m_loadedAmmoNumbers0 = nullptr;

	GameObject* m_ammoObj1 = nullptr;

	Numbers* m_ammoNumbers1 = nullptr;

	GameObject* m_loadedAmmoObj1 = nullptr;

	Numbers* m_loadedAmmoNumbers1 = nullptr;

	GameObject* m_ammoTypeObj0 = nullptr;

	UserMeshRenderer* m_ammoTypeRenderer0 = nullptr;

	GameObject* m_ammoTypeObj1 = nullptr;

	UserMeshRenderer* m_ammoTypeRenderer1 = nullptr;

	Texture* m_ammoTexture[(unsigned int)AmmoTypes::Max] = {};

	GameObject* m_screenEffectObj = nullptr;

	UserMeshRenderer* m_screenEffectRenderer = nullptr;

	Texture* m_redScreenEffectTexture = nullptr;

	Texture* m_greenScreenEffectTexture = nullptr;

	Texture* m_blueScreenEffectTexture = nullptr;
};

