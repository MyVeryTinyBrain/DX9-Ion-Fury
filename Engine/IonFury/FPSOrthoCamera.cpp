#include "stdafx.h"
#include "FPSOrthoCamera.h"
#include "LeftHandAnimator.h"
#include "RightHandAnimator.h"

void FPSOrthoCamera::Awake()
{
	m_camera = gameObject->AddComponent<Camera>();
	m_camera->cameraOrder = 100;
	m_camera->overlapMode = true;
	m_camera->allowRenderLayers = (1 << 5);
	m_camera->projectionMode = ProjectionMode::Orthographic;

	m_forwardGameObject = CreateGameObjectToChild(gameObject->transform);
	m_forwardGameObject->transform->localPosition = Vec3(0, 0, 1);

	m_hudObject = CreateGameObjectToChild(m_forwardGameObject->transform);
	{
		auto crosshairObj = CreateGameObjectToChild(m_hudObject->transform);
		crosshairObj->transform->scale = Vec3(0.035f, 0.035f, 0.035f);

		auto renderer = crosshairObj->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
		renderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
		renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/hud/crosshair.png"));
		renderer->renderLayerIndex = 5;
	}

	m_handsObject = CreateGameObjectToChild(m_forwardGameObject->transform);
	m_handsObject->transform->localPosition = Vec2(0, 0);

	m_handsChildObject = CreateGameObjectToChild(m_handsObject->transform);

	//m_leftHandGameObject = CreateGameObjectToChild(m_handsChildObject->transform);
	//m_leftHandAnimator = m_leftHandGameObject->AddComponent<LeftHandAnimator>();
	//{
	//	auto renderer = m_leftHandGameObject->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	//	renderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	//	renderer->renderLayerIndex = 31;
	//}

	m_rightHandGameObject = CreateGameObjectToChild(m_handsChildObject->transform);
	m_rightHandGameObject->transform->localPosition = Vec2(0, -0.2f);
	m_rightHandAnimator = m_rightHandGameObject->AddComponent<RightHandAnimator>();
	{
		auto renderer = m_rightHandGameObject->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
		renderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
		renderer->renderLayerIndex = 5;
	}
}

void FPSOrthoCamera::LateUpdate()
{
	if (m_isWalking)
	{
		float handsMove = (sinf(m_elapsed * 7.5f - PI * 0.5f) + 1.0f) * 0.05f;
		m_handsObject->transform->localPosition = Vec2(handsMove, -handsMove * 0.5f);
		m_elapsed += Time::DeltaTime();
		m_isWalking = false;
	}
	else
	{
		m_handsObject->transform->localPosition = Vec2::Lerp(m_handsObject->transform->localPosition, Vec2::zero(), Time::UnscaledDelteTime() * 10.0f);
		m_elapsed = 0;
	}

	m_handsChildObject->transform->localPosition = Vec2::Lerp(m_handsChildObject->transform->localPosition, Vec2::zero(), Time::UnscaledDelteTime() * 10.0f);
}

Camera* FPSOrthoCamera::GetCamera() const
{
	return m_camera;
}

Transform* FPSOrthoCamera::GetForwardTransform() const
{
	return m_forwardGameObject->transform;
}

LeftHandAnimator* FPSOrthoCamera::GetLeftHandAnimator() const
{
	return m_leftHandAnimator;
}

RightHandAnimator* FPSOrthoCamera::GetRightHandAnimator() const
{
	return m_rightHandAnimator;
}

void FPSOrthoCamera::MoveHands(const Vec3& deltaAngle)
{
	const float clampRange = 0.5f;
	Vec3 clampedDeltaAngle = deltaAngle * (1.0f / 360.0f);
	clampedDeltaAngle.x = Clamp(clampedDeltaAngle.x, -clampRange, +clampRange);
	clampedDeltaAngle.y = Clamp(clampedDeltaAngle.y, -clampRange, +clampRange);

	Vec2 localPosition = m_handsChildObject->transform->localPosition + Vec2(-clampedDeltaAngle.y, clampedDeltaAngle.x);
	localPosition.x = Clamp(localPosition.x, -0.5f, +0.5f);
	localPosition.y = Clamp(localPosition.y, -0.5f, +0.2f);
	m_handsChildObject->transform->localPosition = localPosition;
}

void FPSOrthoCamera::SetWalkingState(bool value)
{
	m_isWalking = value;
}
