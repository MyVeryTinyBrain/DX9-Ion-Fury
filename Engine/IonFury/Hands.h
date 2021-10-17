#pragma once

#include "WeaponTypes.h"
#include "AmmoTypes.h"

class Hands : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

public:

	void SetWalkingState(bool value);

	void SetElaptionAccumulateScale(float value);

	void MoveHandsChildObject(const Vec3& deltaAngle);

	void SetActiveWeapon(int weaponIndex);

	void AddAmmo(WeaponTypes weapon, AmmoTypes ammo, unsigned int count);

	class Weapon* GetActiveWeapon() const;

private:

	void SetupWeapons();

	void InputToActiveWeapon();

	void MoveHandsObject();

	void RepositionHandsChildObject();

	void ChangeWeapon();

private:

	// 이동시 무기를 흔드는데 사용되는 게임오브젝트입니다.

	GameObject* m_handsObject = nullptr;

	// 걷고 있음을 나타내는 플래그입니다.
	// 외부에서 설정됩니다.

	bool m_isWalking = false;

	// 걸을때 무기 흔들림을 위한 걷기 시간이 누적된 값입니다.

	float m_elapsed = 0;

	// 걷기 시간을 누적할때 곱해지는 스케일입니다.
	// 이 값으로 인해 무기가 흔들리는 속도가 변경됩니다.

	float m_elapionAccumulateScale = 1.0f;

	// 무기전환 모션에 사용되는 게임오브젝트입니다.

	GameObject* m_handsMiddleObject = nullptr;

	// 교체될 무기의 인덱스입니다.

	int m_weaponChangeIndex = -1;

	// 무기 교체까지 남은 시간입니다.
	// 이 시간에 따라서 무기교체 모션이 재생됩니다.

	float m_weaponChangingCounter = 0;

	const Vec2 m_handsMiddleShowLocalPosition = Vec2::zero();

	const Vec2 m_handsMiddleHideLocalPosition = Vec2(0, -1.0f);

	// 화면각도 변경시 무기를 따라오는 동작을 구현하는 게임오브젝트입니다.

	GameObject* m_handsChildObject = nullptr;

	GameObject* m_weaponObjects[(unsigned int)WeaponTypes::Max];

	class Weapon* m_weapons[(unsigned int)WeaponTypes::Max];

	// 활성화된 무기 인덱스입니다.

	int m_activeWeaponIndex = -1;
};

