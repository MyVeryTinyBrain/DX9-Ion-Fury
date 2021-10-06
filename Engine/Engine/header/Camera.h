#pragma once

#include "Component.h"

enum class ProjectionMode
{
	Perspective,
	Orthographic,
};

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

	ProjectionMode GetProjectionMode() const;

	void SetProjectionMode(ProjectionMode mode);

	__declspec(property(get = GetProjectionMode, put = SetProjectionMode)) ProjectionMode mode;

public:

	static Camera* GetMainCamera();

	static void SetMainCamera(Camera* camera);

private:

	int m_cameraIndex = 0;

	bool m_overlap = true;

	// Perspective 

	float m_fovAngle;

	float m_aspect;

	float m_near;

	float m_far;

	bool m_isPerspective;

	// Orthographic

	float m_width;

	float m_height;

	// Mode

	ProjectionMode m_projectionMode = ProjectionMode::Perspective;

	// Render target

	class Texture* m_rednerTexture = nullptr;

private:

	static std::mutex g_mutex;

	static Camera* g_mainCamera;

	static std::list<Camera*> g_cameras;

};

