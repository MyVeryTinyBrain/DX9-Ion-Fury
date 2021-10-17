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

	// �̵��� ���⸦ ���µ� ���Ǵ� ���ӿ�����Ʈ�Դϴ�.

	GameObject* m_handsObject = nullptr;

	// �Ȱ� ������ ��Ÿ���� �÷����Դϴ�.
	// �ܺο��� �����˴ϴ�.

	bool m_isWalking = false;

	// ������ ���� ��鸲�� ���� �ȱ� �ð��� ������ ���Դϴ�.

	float m_elapsed = 0;

	// �ȱ� �ð��� �����Ҷ� �������� �������Դϴ�.
	// �� ������ ���� ���Ⱑ ��鸮�� �ӵ��� ����˴ϴ�.

	float m_elapionAccumulateScale = 1.0f;

	// ������ȯ ��ǿ� ���Ǵ� ���ӿ�����Ʈ�Դϴ�.

	GameObject* m_handsMiddleObject = nullptr;

	// ��ü�� ������ �ε����Դϴ�.

	int m_weaponChangeIndex = -1;

	// ���� ��ü���� ���� �ð��Դϴ�.
	// �� �ð��� ���� ���ⱳü ����� ����˴ϴ�.

	float m_weaponChangingCounter = 0;

	const Vec2 m_handsMiddleShowLocalPosition = Vec2::zero();

	const Vec2 m_handsMiddleHideLocalPosition = Vec2(0, -1.0f);

	// ȭ�鰢�� ����� ���⸦ ������� ������ �����ϴ� ���ӿ�����Ʈ�Դϴ�.

	GameObject* m_handsChildObject = nullptr;

	GameObject* m_weaponObjects[(unsigned int)WeaponTypes::Max];

	class Weapon* m_weapons[(unsigned int)WeaponTypes::Max];

	// Ȱ��ȭ�� ���� �ε����Դϴ�.

	int m_activeWeaponIndex = -1;
};

