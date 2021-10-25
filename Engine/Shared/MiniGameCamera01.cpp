#include "shared_stdafx.h"
#include "MiniGameCamera01.h"
#include "OverlayRenderOrders.h"
#include "RenderLayers.h"
#include "Player.h"

void MiniGameCamera01::Awake()
{
	if (!Player::GetInstance())
	{
		return;
	}

	Transform* PlayerTransform = Player::GetInstance()->transform;
	transform->SetParent(PlayerTransform);

	m_CameraObject = CreateGameObjectToChild(transform);

	m_Camera = m_CameraObject->AddComponent<Camera>();
	m_Camera->cameraOrder = 100;
	m_Camera->overlapMode = true;
	m_Camera->allowRenderLayers = (1 << uint8_t(RenderLayers::Overlay));
	m_Camera->projectionMode = ProjectionMode::Orthographic;

	MiniGameBackgroundObject = CreateGameObjectToChild(transform);
	MiniGameBackgroundObject->transform->SetParent(PlayerTransform);
	MiniGameBackgroundObject->transform->localPosition = Vec3(0, 0, 1);
	UserMeshRenderer* BackgroundRenderer = MiniGameBackgroundObject->AddComponent<UserMeshRenderer>();
	BackgroundRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	BackgroundRenderer->SetTexture(0, Resource::FindAs<Texture>(BuiltInWhiteTexture));
}
