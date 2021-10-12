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
	m_rightHandRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerLeftHand);

	m_leftHandObj = CreateGameObjectToChild(transform);
	m_leftHandRenderer = m_leftHandObj->AddComponent<UserMeshRenderer>();
	m_leftHandRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_leftHandRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_leftHandRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_leftHandRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerRightHand);
}
