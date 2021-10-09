#pragma once

class FPSOrthoCamera;

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

	FPSOrthoCamera* m_orthoCamera = nullptr;

	float m_sensitivity = 0.2f;

	bool m_aimming = true;
};

