#pragma once

#include "Component.h"

class Camera : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

public:

	Mat4 GetWorldToViewMatrix() const;

	Mat4 GetViewToWorldMatrix() const;

	Mat4 GetViewToProjectionMatrix() const;

	Mat4 GetProjectionToViewMatrix() const;

	__declspec(property(get = GetWorldToViewMatrix)) Mat4 worldToView;

	__declspec(property(get = GetViewToWorldMatrix)) Mat4 viewToWorld;

	__declspec(property(get = GetViewToProjectionMatrix)) Mat4 viewToProjection;

	__declspec(property(get = GetProjectionToViewMatrix)) Mat4 projectionToView;

public:

	static Camera* GetMainCamera();

	static void SetMainCamera(Camera* camera);

private:

	float m_fovAngle;

	float m_aspect;

	float m_near;

	float m_far;

	bool m_isPerspective;

private:

	static std::mutex g_mutex;

	static Camera* g_mainCamera;

	static std::vector<Camera*> g_cameras;

};

