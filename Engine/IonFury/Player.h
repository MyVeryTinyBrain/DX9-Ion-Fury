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

	void AddHP(int hp);

	void SetHP(int hp);

	int GetHP() const;

	void AddAmmo(WeaponTypes weapon, AmmoTypes ammo, unsigned int count);

	__declspec(property(get = GetHP, put = SetHP)) int HP;

private:

	FPSCharacterController* m_controller = nullptr;

	int m_hp = 100;
};

