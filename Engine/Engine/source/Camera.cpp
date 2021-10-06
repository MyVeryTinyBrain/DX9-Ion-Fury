#include "EngineBase.h"
#include "Camera.h"
#include "Transform.h"
#include "GraphicDevice.h"

std::mutex Camera::g_mutex;

Camera* Camera::g_mainCamera = nullptr;

std::list<Camera*> Camera::g_cameras;

void Camera::Awake()
{
	m_fovAngle = 90;

	m_aspect = GraphicDevice::GetInstance()->GetAspect();

	m_near = 0.1f;

	m_far = 1000.0f;

	m_isPerspective = true;

	m_width = GraphicDevice::GetInstance()->GetSize().x * 0.1f;

	m_height = GraphicDevice::GetInstance()->GetSize().y * 0.1f;

	g_mutex.lock();

	if (!g_mainCamera)
	{
		g_mainCamera = this;
	}

	g_cameras.push_back(this);

	g_mutex.unlock();
}

void Camera::OnDestroy()
{
	g_mutex.lock();

	auto find_it = FindInContainer(g_cameras, this);

	if (find_it != g_cameras.end())
		g_cameras.erase(find_it);

	if (g_mainCamera == this && g_cameras.size() > 0)
		g_mainCamera = g_cameras.front();

	g_mutex.unlock();
}

Mat4 Camera::GetWorldToViewMatrix() const
{
	return transform->worldToLocal;
}

Mat4 Camera::GetViewToWorldMatrix() const
{
	return transform->localToWorld;
}

Mat4 Camera::GetViewToProjectionMatrix() const
{
	Mat4 toProj;

	switch (m_projectionMode)
	{
		case ProjectionMode::Perspective:
			D3DXMatrixPerspectiveFovLH(&toProj, m_fovAngle * Deg2Rad, m_aspect, m_near, m_far);
			break;
		case ProjectionMode::Orthographic:
			D3DXMatrixOrthoLH(&toProj, m_width, m_height, m_near, m_far);
			break;
	}

	return toProj;
}

Mat4 Camera::GetProjectionToViewMatrix() const
{
	return GetViewToProjectionMatrix().inversed();
}

ProjectionMode Camera::GetProjectionMode() const
{
	return m_projectionMode;
}

void Camera::SetProjectionMode(ProjectionMode mode)
{
	m_projectionMode = mode;
}

Camera* Camera::GetMainCamera()
{
	std::unique_lock<std::mutex> lock(g_mutex);

	return g_mainCamera;
}

void Camera::SetMainCamera(Camera* camera)
{
	std::unique_lock<std::mutex> lock(g_mutex);

	g_mainCamera = camera;
}
