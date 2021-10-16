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

	// 이 무기로 변경되었을 떄 호출됩니다.
	virtual void OnChanged() = 0;

	// 이 무기를 집어 넣을 때 호출됩니다.
	virtual void OnPutIn() = 0;

	// 공격 키 상태가 전송됩니다.
	virtual void OnAttackInput(InputType inputType) = 0;

	// 보조 키 상태가 전송됩니다.
	virtual void OnSubInput(InputType inputType) = 0;

	// 재장전 키 상태가 전송됩니다.
	virtual void OnReloadInput(InputType inputType) = 0;

	// 0번째 탄약 타입을 반환합니다.
	virtual AmmoTypes GetAmmoType0() const = 0;

	// 1번째 탄약 타입을 반환합니다.
	virtual AmmoTypes GetAmmoType1() const = 0;

	// 0번째 탄약 총 보유갯수를 반환합니다.
	virtual unsigned int GetTotalAmmo0() const = 0;

	// 1번째 탄약의 총 보유갯수를 반환합니다.
	virtual unsigned int GetTotalAmmo1() const = 0;

	// 0번째 탄약의 장전된 갯수를 반환합니다.
	virtual unsigned int GetLoadedAmmo0() const = 0;

	// 1번째 탄약의 장전된 갯수를 반환합니다.
	virtual unsigned int GetLoadedAmmo1() const = 0;

	// 0번째 탄약의 장전상태가 유효한지 반환합니다.
	virtual bool GetLoadedAmmo0State() const = 0;

	// 1번째 탄약의 장전상태가 유효한지 반환합니다.
	virtual bool GetLoadedAmmo1State() const = 0;

	// 탄약을 추가합니다.
	virtual void AddAmmo(AmmoTypes ammo, unsigned int count) = 0;
};

