#pragma once

class MiniGameCamera01 : public Component
{
public:

	OverrideComponentFunction(Awake);

private:

	GameObject* m_CameraObject = nullptr;

	Camera* m_Camera = nullptr;

	GameObject* MiniGameBackgroundObject = nullptr;
};

