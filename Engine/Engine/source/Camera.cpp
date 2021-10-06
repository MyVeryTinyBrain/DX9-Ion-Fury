#include "EngineBase.h"
#include "Camera.h"
#include "Transform.h"
#include "GraphicDevice.h"

Camera* Camera::g_mainCamera = nullptr;

std::vector<Camera*> Camera::g_cameras;

void Camera::Awake()
{
	m_fovAngle = 90;

	m_aspect = GraphicDevice::GetInstance()->GetDeviceAspect();

	m_near = 0.1f;

	m_far = 1000.0f;

	m_isPerspective = true;

	if (!g_mainCamera)
	{
		g_mainCamera = this;
	}

	g_cameras.push_back(this);

	SortCamerasByOrder();
}

void Camera::OnDestroy()
{
	auto find_it = FindInContainer(g_cameras, this);

	if (find_it != g_cameras.end())
		g_cameras.erase(find_it);

	g_mainCamera = nullptr;

	if (g_mainCamera == this && g_cameras.size() > 0)
		g_mainCamera = g_cameras.front();

	SortCamerasByOrder();
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
			{
				D3DXMatrixPerspectiveFovLH(&toProj, m_fovAngle * Deg2Rad, m_aspect, m_near, m_far);
			}
			break;
		case ProjectionMode::Orthographic:
			{
				float width = m_aspect / 1.0f;
				float height = 1.0f;
				D3DXMatrixOrthoLH(&toProj, width * m_orthographicSize, height * m_orthographicSize, m_near, m_far);
			}
			break;
	}

	return toProj;
}

Mat4 Camera::GetProjectionToViewMatrix() const
{
	return GetViewToProjectionMatrix().inversed();
}

float Camera::GetFOV() const
{
	return m_fovAngle;
}

void Camera::SetFOV(float angle)
{
	m_fovAngle = angle;
}

float Camera::GetOrthographicSize() const
{
	return m_orthographicSize;
}

void Camera::SetOrthographicSize(float value)
{
	m_orthographicSize = value;
}

int Camera::GetCameraOrder() const
{
	return m_cameraOrder;
}

void Camera::SetCameraOrder(int value)
{
	m_cameraOrder = value;
	SortCamerasByOrder();
}

bool Camera::IsOverlapMode() const
{
	return m_overlap;
}

void Camera::SetOverlapMode(bool value)
{
	m_overlap = value;
}

uint32_t Camera::GetAllowRenderLayers() const
{
	return m_allowRenderLayers;
}

void Camera::SetAllowRenderLayers(uint32_t value)
{
	m_allowRenderLayers = value;
}

ProjectionMode Camera::GetProjectionMode() const
{
	return m_projectionMode;
}

void Camera::SetProjectionMode(ProjectionMode mode)
{
	m_projectionMode = mode;
}

const Ref<RenderTexture>& Camera::GetRenderTexture() const
{
	return m_renderTexture;
}

void Camera::SetRenderTexture(const Ref<RenderTexture>& value)
{
	m_renderTexture = value;
}

Camera* Camera::GetMainCamera()
{
	return g_mainCamera;
}

void Camera::SetMainCamera(Camera* camera)
{
	g_mainCamera = camera;
}

size_t Camera::GetCameraCount()
{
	return g_cameras.size();;
}

Camera* Camera::GetCamera(unsigned int index)
{
	return g_cameras[index];
}

void Camera::SortCamerasByOrder()
{
	std::sort(
		g_cameras.begin(),
		g_cameras.end(),
		[](Camera* lhs, Camera* rhs)
		{
			return lhs->m_cameraOrder < rhs->m_cameraOrder;
		});
}
