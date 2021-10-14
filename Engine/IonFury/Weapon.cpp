#include "stdafx.h"
#include "Weapon.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"

void Weapon::Awake()
{
	m_rightHandObj = CreateGameObjectToChild(transform);
	m_rightHandRenderer = m_rightHandObj->AddComponent<UserMeshRenderer>();
	m_rightHandRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_rightHandRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_rightHandRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_rightHandRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerRightHand);
}
