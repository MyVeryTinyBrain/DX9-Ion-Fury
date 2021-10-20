#pragma once

#include "WeaponTypes.h"
#include "AmmoTypes.h"

class FPSCharacterController;
class FPSCamera;
class FPSOrthoCamera;

class Player : public Component
{
	DeclareStaticComponent(Player);

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(FixedUpdate);

public:

	FPSCharacterController* GetController() const;

	Camera* GetPerspectiveCamera() const;

	FPSCamera* GetFPSCamera() const;

	FPSOrthoCamera* GetOrthoCamera() const;

	__declspec(property(get = GetController)) FPSCharacterController* controller;

	__declspec(property(get = GetPerspectiveCamera)) Camera* perspectiveCamera;

	__declspec(property(get = GetFPSCamera)) FPSCamera* fpsCamera;

	__declspec(property(get = GetOrthoCamera)) FPSOrthoCamera* orthoCamera;

public:

	void AddHP(unsigned int hp, bool effect = true);

	void SubtractHP(unsigned int hp, bool effect = true);

	void AddArmor(unsigned int armor, bool effect = true);

	void SubtractArmor(unsigned int armor, bool effect = true);

	void SetRigidCounter(float value);

	void TakeDamage(int damage, const Vec3& velocity = Vec3::zero(), float rigidTime = 0.0f);

	void SetHP(unsigned int hp);

	int GetHP() const;

	int GetArmor() const;

	void AddAmmo(WeaponTypes weapon, AmmoTypes ammo, unsigned int count, bool effect = true);

	__declspec(property(get = GetHP, put = SetHP)) int HP;

	__declspec(property(get = GetArmor, put = SetArmor)) int Armor;

private:

	FPSCharacterController* m_controller = nullptr;

	int m_hp = 100;

	int m_armor = 0;

	float m_rigidCounter = 0;

	Vec3 m_damagedVelocity = Vec3::zero();
};

