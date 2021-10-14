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

public:

	void MakeRecoil(const Vec2& velocity, float time, float recoilPow = 1.0f);

private:

	void MoveMouseToCenter();

	void Recoiling();

private:

	Camera* m_camera = nullptr;

	FPSOrthoCamera* m_orthoCamera = nullptr;

	float m_sensitivity = 0.2f;

	bool m_aimming = true;

	Vec2 m_recoilVelocity;

	float m_recoilCounter = 0;

	float m_recoilMaxTime;

	float m_recoilPow = 1.0f;
};

