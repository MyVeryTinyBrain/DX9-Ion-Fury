#include "shared_stdafx.h"
#include "FPSCamera.h"
#include "FPSOrthoCamera.h"
#include "PhysicsLayers.h"
#include "Trigger.h"

void FPSCamera::Awake()
{
	ShowCursor(false);
	
	m_camera = gameObject->AddComponent<Camera>();
	m_camera->fov = m_defaultFOV;
	m_camera->allowRenderLayers = (1 << 0);
	Camera::SetMainCamera(m_camera);

	m_orthoCamera = gameObject->AddComponent<FPSOrthoCamera>();

	MoveMouseToCenter();

	// 난 이 감도가 편함.
	m_sensitivity = 0.15f;
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

		float fovPercent = m_camera->fov / m_defaultFOV;

		Vec2 deltaMouse = (centerMouse - beforeMouse) * fovPercent;
		Vec3 rotateAngle = Vec3(deltaMouse.y, deltaMouse.x, 0) * m_sensitivity;

		angle -= rotateAngle;
		angle.x = MathEx::Clamp(angle.x, -85, +85);
		angle.z = MathEx::Clamp(angle.z, -85, +85);
		
		{
			Vec3 realDeltaAngle = angle - beforeAngle;
			m_orthoCamera->MoveHandsChildObject(realDeltaAngle);
		}

		transform->eulerAngle = angle;
	}

	Recoiling();

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

void FPSCamera::MakeRecoil(const Vec2& velocity, float time, float recoilPow)
{
	m_recoilVelocity = velocity;
	m_recoilCounter = time;
	m_recoilMaxTime = time;
	m_recoilPow = recoilPow;
}

void FPSCamera::MoveMouseToCenter()
{
	RECT rect;
	GetClientRect(GraphicDevice::GetInstance()->GetWindowHandle(), &rect);
	POINT center = { LONG(rect.right * 0.5f), LONG(rect.bottom * 0.5f) };
	ClientToScreen(GraphicDevice::GetInstance()->GetWindowHandle(), &center);
	SetCursorPos(center.x, center.y);
}

void FPSCamera::Recoiling()
{
	if (m_recoilCounter > 0 && 
		m_recoilMaxTime != 0)
	{
		float powerPercent = m_recoilCounter / m_recoilMaxTime;
		powerPercent = powf(powerPercent, m_recoilPow);

		Vec2 recoilVelocity = m_recoilVelocity * powerPercent;
		Vec3 angle = transform->eulerAngle;
		angle += Vec3(-recoilVelocity.y, recoilVelocity.x, 0) * Time::TimeScale();
		angle.x = MathEx::Clamp(angle.x, -85, +85);
		angle.z = MathEx::Clamp(angle.z, -85, +85);
		transform->eulerAngle = angle;

		m_recoilCounter -= Time::DeltaTime();
	}
}

void FPSCamera::UseInput()
{
	PhysicsRay ray(m_camera->transform->position, m_camera->transform->forward, 1.5f);
	RaycastHit hit;
	bool result =
		Physics::Raycast(
			hit,
			ray,
			1 << (uint8_t)PhysicsLayers::InputTrigger | 1 << (uint8_t)PhysicsLayers::Terrain,
			PhysicsQueryType::Trigger);

	if (result && hit.collider->layerIndex == (uint8_t)PhysicsLayers::InputTrigger)
	{
		Trigger* trigger = hit.collider->rigidbody->gameObject->GetComponent<Trigger>();

		if (trigger)
		{
			trigger->Use();
		}
	}
}
