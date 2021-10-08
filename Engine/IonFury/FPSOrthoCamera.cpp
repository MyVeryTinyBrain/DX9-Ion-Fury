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

	//m_leftHandGameObject = CreateGameObjectToChild(m_forwardGameObject->transform);
	//m_leftHandAnimator = m_leftHandGameObject->AddComponent<LeftHandAnimator>();
	//{
	//	auto renderer = m_leftHandGameObject->AddComponent<UserMeshRenderer>();
	//	renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	//	renderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	//	renderer->renderLayerIndex = 31;
	//}

	m_rightHandGameObject = CreateGameObjectToChild(m_forwardGameObject->transform);
	m_rightHandAnimator = m_rightHandGameObject->AddComponent<RightHandAnimator>();
	{
		auto renderer = m_rightHandGameObject->AddComponent<UserMeshRenderer>();
		renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
		renderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
		renderer->renderLayerIndex = 5;
	}
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
