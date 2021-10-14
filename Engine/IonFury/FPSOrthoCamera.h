#pragma once

#include "WeaponTypes.h"

class FPSCamera;

class FPSOrthoCamera : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

public:

	Camera* GetCamera() const;

	Transform* GetForwardTransform() const;

	__declspec(property(get = GetCamera)) Camera* camera;

	__declspec(property(get = GetForwardTransform)) Transform* forwardTransform;

public:

	void MoveHandsChildObject(const Vec3& deltaAngle);

	void SetWalkingState(bool value);

	void SetElaptionAccumulateScale(float value);

	void SetCrossHair(bool value);

	void SetActiveWeapon(int weaponIndex);

private:

	void SetupWeapons();

	void InputToActiveWeapon();

	void MoveHandsObject();

	void RepositionHandsChildObject();

	void ChangeWeapon();

private:

	Camera* m_camera = nullptr;

	GameObject* m_forwardGameObject = nullptr;

	GameObject* m_hudObject = nullptr;

	UserMeshRenderer* m_crosshairRenderer = nullptr;

	// �̵��� ���⸦ ���µ� ���Ǵ� ���ӿ�����Ʈ�Դϴ�.

	GameObject* m_handsObject = nullptr;

	// ������ȯ ��ǿ� ���Ǵ� ���ӿ�����Ʈ�Դϴ�.

	GameObject* m_handsMiddleObject = nullptr;

	// ��ü�� ������ �ε����Դϴ�.

	int m_weaponChangeIndex = -1;

	// ���� ��ü���� ���� �ð��Դϴ�.
	// �� �ð��� ���� ���ⱳü ����� ����˴ϴ�.

	float m_weaponChangingCounter = 0;

	const Vec2 m_handsMiddleShowLocalPosition = Vec2::zero();

	const Vec2 m_handsMiddleHideLocalPosition = Vec2(-0.2f, -1.0f);

	const Vec3 m_handsMiddleShowLocalEulerAngle = Vec3(0, 0, 0);

	const Vec3 m_handsMiddleHideLocalEulerAngle = Vec3(0, 0, 50);

	// ȭ�鰢�� ����� ���⸦ ������� ������ �����ϴ� ���ӿ�����Ʈ�Դϴ�.

	GameObject* m_handsChildObject = nullptr;

	GameObject* m_weaponObjects[(unsigned int)WeaponTypes::Max];

	class Weapon* m_weapons[(unsigned int)WeaponTypes::Max];

	// Ȱ��ȭ�� ���� �ε����Դϴ�.

	int m_activeWeaponIndex = -1;

	// �Ȱ� ������ ��Ÿ���� �÷����Դϴ�.
	// �ܺο��� �����˴ϴ�.

	bool m_isWalking = false;

	// ������ ���� ��鸲�� ���� �ȱ� �ð��� ������ ���Դϴ�.

	float m_elapsed = 0;

	// �ȱ� �ð��� �����Ҷ� �������� �������Դϴ�.
	// �� ������ ���� ���Ⱑ ��鸮�� �ӵ��� ����˴ϴ�.

	float m_elapionAccumulateScale = 1.0f;
};

