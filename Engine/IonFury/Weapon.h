#pragma once

#include "AmmoTypes.h"

class FPSOrthoCamera;

class Weapon abstract : public Component
{
public:

	enum class InputType
	{
		KeyDown, KeyPressing, KeyUp, Nothing
	};

public:

	// �� ����� ����Ǿ��� �� ȣ��˴ϴ�.
	virtual void OnChanged() = 0;

	// �� ���⸦ ���� ���� �� ȣ��˴ϴ�.
	virtual void OnPutIn() = 0;

	// ���� Ű ���°� ���۵˴ϴ�.
	virtual void OnAttackInput(InputType inputType) = 0;

	// ���� Ű ���°� ���۵˴ϴ�.
	virtual void OnSubInput(InputType inputType) = 0;

	// ������ Ű ���°� ���۵˴ϴ�.
	virtual void OnReloadInput(InputType inputType) = 0;

	// 0��° ź�� Ÿ���� ��ȯ�մϴ�.
	virtual AmmoTypes GetAmmoType0() const = 0;

	// 1��° ź�� Ÿ���� ��ȯ�մϴ�.
	virtual AmmoTypes GetAmmoType1() const = 0;

	// 0��° ź�� �� ���������� ��ȯ�մϴ�.
	virtual unsigned int GetTotalAmmo0() const = 0;

	// 1��° ź���� �� ���������� ��ȯ�մϴ�.
	virtual unsigned int GetTotalAmmo1() const = 0;

	// 0��° ź���� ������ ������ ��ȯ�մϴ�.
	virtual unsigned int GetLoadedAmmo0() const = 0;

	// 1��° ź���� ������ ������ ��ȯ�մϴ�.
	virtual unsigned int GetLoadedAmmo1() const = 0;

	// 0��° ź���� �������°� ��ȿ���� ��ȯ�մϴ�.
	virtual bool GetLoadedAmmo0State() const = 0;

	// 1��° ź���� �������°� ��ȿ���� ��ȯ�մϴ�.
	virtual bool GetLoadedAmmo1State() const = 0;

	// ź���� �߰��մϴ�.
	virtual void AddAmmo(AmmoTypes ammo, unsigned int count) = 0;
};

