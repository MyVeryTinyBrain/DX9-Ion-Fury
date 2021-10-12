#pragma once

#include "WeaponTypes.h"

class LeftHandAnimator;
class RightHandAnimator;

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

	void SetActiveWeapon(unsigned int weaponIndex);

private:

	void SetupWeapons();

	void InputToActiveWeapon();

	void MoveHandsObject();

	void RepositionHandsChildObject();

private:

	Camera* m_camera = nullptr;

	GameObject* m_forwardGameObject = nullptr;

	GameObject* m_hudObject = nullptr;

	UserMeshRenderer* m_crosshairRenderer = nullptr;

	GameObject* m_handsObject = nullptr;

	GameObject* m_handsChildObject = nullptr;

	GameObject* m_weaponObjects[(unsigned int)WeaponTypes::Max];

	class Weapon* m_weapons[(unsigned int)WeaponTypes::Max];

	int m_activeWeaponIndex = 0;

	bool m_isWalking = false;

	float m_elapsed = 0;

	float m_elapionAccumulateScale = 1.0f;
};

