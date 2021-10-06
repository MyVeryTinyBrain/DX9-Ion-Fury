#pragma once

class FPSCamera : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	Camera* GetCamera() const;

	__declspec(property(get = GetCamera)) Camera* camera;

private:

	void MoveMouseToCenter();

private:

	Camera* m_camera = nullptr;

	float m_sensitivity = 0.5f;

	bool m_aimming = true;
};

