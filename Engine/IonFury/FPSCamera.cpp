#include "stdafx.h"
#include "FPSCamera.h"
#include "FPSOrthoCamera.h"

void FPSCamera::Awake()
{
	ShowCursor(false);

	m_camera = gameObject->AddComponent<Camera>();
	m_camera->allowRenderLayers = (1 << 0);
	Camera::SetMainCamera(m_camera);

	m_orthoCamera = gameObject->AddComponent<FPSOrthoCamera>();

	MoveMouseToCenter();
}

void FPSCamera::Update()
{
	if (m_aimming)
	{
		Vec3 angle = transform->eulerAngle;
		Vec3 beforeAngle = angle;

		Vec2 beforeMouse = Input::GetMousePositionInViewport();
		MoveMouseToCenter();
		Vec2 centerMouse = Input::GetMousePositionInViewport();

		Vec2 deltaMouse = centerMouse - beforeMouse;
		Vec3 rotateAngle = Vec3(deltaMouse.y, deltaMouse.x, 0) * m_sensitivity;

		angle -= rotateAngle;
		angle.x = MathEx::Clamp(angle.x, -90, +90);
		angle.z = MathEx::Clamp(angle.z, -90, +90);
		
		{
			Vec3 realDeltaAngle = angle - beforeAngle;
			m_orthoCamera->MoveHands(realDeltaAngle);
		}

		transform->eulerAngle = angle;
	}

	if (Input::GetKeyDown(Key::Return))
	{
		m_aimming = !m_aimming;
		ShowCursor(!m_aimming);
	}
}

Camera* FPSCamera::GetCamera() const
{
	return m_camera;
}

FPSOrthoCamera* FPSCamera::GetFPSOrthoCamera() const
{
	return m_orthoCamera;
}

void FPSCamera::MoveMouseToCenter()
{
	RECT rect;
	GetClientRect(GraphicDevice::GetInstance()->GetWindowHandle(), &rect);
	POINT center = { LONG(rect.right * 0.5f), LONG(rect.bottom * 0.5f) };
	ClientToScreen(GraphicDevice::GetInstance()->GetWindowHandle(), &center);
	SetCursorPos(center.x, center.y);
}
