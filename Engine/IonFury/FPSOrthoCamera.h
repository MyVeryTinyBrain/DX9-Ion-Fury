#pragma once

class LeftHandAnimator;
class RightHandAnimator;

class FPSOrthoCamera : public Component
{
	OverrideComponentFunction(Awake);

public:

	Camera* GetCamera() const;

	Transform* GetForwardTransform() const;

	LeftHandAnimator* GetLeftHandAnimator() const;

	RightHandAnimator* GetRightHandAnimator() const;

	__declspec(property(get = GetCamera)) Camera* camera;

	__declspec(property(get = GetForwardTransform)) Transform* forwardTransform;

	__declspec(property(get = GetLeftHandAnimator)) LeftHandAnimator* leftHandAnimator;

	__declspec(property(get = GetRightHandAnimator)) RightHandAnimator* rightHandAnimator;

private:

	Camera* m_camera = nullptr;

	GameObject* m_forwardGameObject = nullptr;

	GameObject* m_leftHandGameObject = nullptr;

	GameObject* m_rightHandGameObject = nullptr;

	LeftHandAnimator* m_leftHandAnimator = nullptr;

	RightHandAnimator* m_rightHandAnimator = nullptr;
};

