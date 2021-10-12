#pragma once

class FPSOrthoCamera;

class FPSCamera : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	Camera* GetCamera() const;

	FPSOrthoCamera* GetFPSOrthoCamera() const;

	__declspec(property(get = GetCamera)) Camera* camera;

	__declspec(property(get = GetFPSOrthoCamera)) FPSOrthoCamera* fpsOrthoCamera;

private:

	void MoveMouseToCenter();

private:

	Camera* m_camera = nullptr;

	FPSOrthoCamera* m_orthoCamera = nullptr;

	float m_sensitivity = 0.2f;

	bool m_aimming = true;
};

