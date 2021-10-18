#pragma once

#include "WeaponTypes.h"

class FPSCamera;

class FPSOrthoCamera : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

public:

	Camera* GetCamera() const;

	Transform* GetForwardTransform() const;

	class PlayerUI* GetUI() const;

	class Hands* GetHands() const;

	__declspec(property(get = GetCamera)) Camera* camera;

	__declspec(property(get = GetForwardTransform)) Transform* forwardTransform;

	__declspec(property(get = GetUI)) PlayerUI* UI;

	__declspec(property(get = GetHands)) Hands* hands;

public:

	void MoveHandsChildObject(const Vec3& deltaAngle);

	void SetWalkingState(bool value);

	void SetElaptionAccumulateScale(float value);

	void SetCrossHair(bool value);

private:

	void UpdateUI();

private:

	Camera* m_camera = nullptr;

	GameObject* m_forwardGameObject = nullptr;

	GameObject* m_hudObject = nullptr;

	UserMeshRenderer* m_crosshairRenderer = nullptr;

	GameObject* m_handsObj = nullptr;

	class Hands* m_hands = nullptr;

	class PlayerUI* m_ui = nullptr;
};

