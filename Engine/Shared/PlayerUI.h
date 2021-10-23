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

	void SetArmor(unsigned int value);

	void SetLoadedAmmo0State(bool value);

	void SetLoadedAmmo1State(bool value);

	void SetLoadedAmmo0(unsigned int value);

	void SetLoadedAmmo1(unsigned int value);

	void SetAmmo0(unsigned int value);

	void SetAmmo1(unsigned int value);

	void SetAmmo0Type(AmmoTypes type);

	void SetAmmo1Type(AmmoTypes type);

	void SetCardKey(bool value);

private:

	// Player face

	GameObject* m_playerFaceObj = nullptr;

	UserMeshRenderer* m_playerFaceRenderer = nullptr;

	Texture* m_playerFaceTexture[4] = {};

	// HP

	GameObject* m_hpObj = nullptr;

	Numbers* m_hpNumbers = nullptr;

	// Armor image

	GameObject* m_armorImageObj = nullptr;

	UserMeshRenderer* m_armorImageRenderer = nullptr;

	// Armor

	GameObject* m_armorObj = nullptr;

	Numbers* m_armorNumbers = nullptr;

	// Cardkey

	GameObject* m_cardKeyObj = nullptr;

	UserMeshRenderer* m_cardKeyRenderer = nullptr;

	// Total ammo 0

	GameObject* m_ammoObj0 = nullptr;

	Numbers* m_ammoNumbers0 = nullptr;

	// Loaded ammo0

	GameObject* m_loadedAmmoObj0 = nullptr;

	Numbers* m_loadedAmmoNumbers0 = nullptr;

	// Total ammo1

	GameObject* m_ammoObj1 = nullptr;

	Numbers* m_ammoNumbers1 = nullptr;

	// Loaded ammo1

	GameObject* m_loadedAmmoObj1 = nullptr;

	Numbers* m_loadedAmmoNumbers1 = nullptr;

	// Ammo0 image

	GameObject* m_ammoTypeObj0 = nullptr;

	UserMeshRenderer* m_ammoTypeRenderer0 = nullptr;

	// Ammo1 image

	GameObject* m_ammoTypeObj1 = nullptr;

	UserMeshRenderer* m_ammoTypeRenderer1 = nullptr;

	// Ammo image textures

	Texture* m_ammoTexture[(unsigned int)AmmoTypes::Max] = {};

	// Screen effect

	GameObject* m_screenEffectObj = nullptr;

	UserMeshRenderer* m_screenEffectRenderer = nullptr;

	Texture* m_redScreenEffectTexture = nullptr;

	Texture* m_greenScreenEffectTexture = nullptr;

	Texture* m_blueScreenEffectTexture = nullptr;
};

