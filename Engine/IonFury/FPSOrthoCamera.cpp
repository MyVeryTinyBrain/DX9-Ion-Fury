#include "stdafx.h"
#include "FPSOrthoCamera.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"
#include "Weapon.h"
#include "Hands.h"
#include "PlayerUI.h"
#include "Player.h"

void FPSOrthoCamera::Awake()
{
	m_camera = gameObject->AddComponent<Camera>();
	m_camera->cameraOrder = 100;
	m_camera->overlapMode = true;
	m_camera->allowRenderLayers = (1 << uint8_t(RenderLayers::Overlay));
	m_camera->projectionMode = ProjectionMode::Orthographic;

	m_forwardGameObject = CreateGameObjectToChild(gameObject->transform);
	m_forwardGameObject->transform->localPosition = Vec3(0, 0, 1);

	m_hudObject = CreateGameObjectToChild(m_forwardGameObject->transform);
	{
		auto crosshairObj = CreateGameObjectToChild(m_hudObject->transform);
		crosshairObj->transform->scale = Vec3(0.035f, 0.035f, 0.035f);

		m_crosshairRenderer = crosshairObj->AddComponent<UserMeshRenderer>();
		m_crosshairRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
		m_crosshairRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
		m_crosshairRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/hud/crosshair.png"));
		m_crosshairRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
		m_crosshairRenderer->overlayRenderOrder = int(OverlayRenderOrders::Crosshair);
	}

	{
		auto uiObj = CreateGameObjectToChild(m_forwardGameObject->transform);
		m_ui = uiObj->AddComponent<PlayerUI>();
	}

	m_handsObj = CreateGameObjectToChild(m_forwardGameObject->transform);
	m_hands = m_handsObj->AddComponent<Hands>();
}

void FPSOrthoCamera::Start()
{
	
}

void FPSOrthoCamera::Update()
{

}

void FPSOrthoCamera::LateUpdate()
{
	UpdateUI();
}

Camera* FPSOrthoCamera::GetCamera() const
{
	return m_camera;
}

Transform* FPSOrthoCamera::GetForwardTransform() const
{
	return m_forwardGameObject->transform;
}

PlayerUI* FPSOrthoCamera::GetUI() const
{
	return m_ui;
}

Hands* FPSOrthoCamera::GetHands() const
{
	return m_hands;
}

void FPSOrthoCamera::MoveHandsChildObject(const Vec3& deltaAngle)
{
	m_hands->MoveHandsChildObject(deltaAngle);
}

void FPSOrthoCamera::SetWalkingState(bool value)
{
	m_hands->SetWalkingState(value);
}

void FPSOrthoCamera::SetElaptionAccumulateScale(float value)
{
	m_hands->SetElaptionAccumulateScale(value);
}

void FPSOrthoCamera::SetCrossHair(bool value)
{
	m_crosshairRenderer->gameObject->activeSelf = value;
}

void FPSOrthoCamera::UpdateUI()
{
	Weapon* weapon = m_hands->GetActiveWeapon();
	m_ui->SetLoadedAmmo0State(weapon->GetLoadedAmmo0State());
	m_ui->SetLoadedAmmo1State(weapon->GetLoadedAmmo1State());
	m_ui->SetLoadedAmmo0(weapon->GetLoadedAmmo0());
	m_ui->SetLoadedAmmo1(weapon->GetLoadedAmmo1());
	m_ui->SetAmmo0Type(weapon->GetAmmoType0());
	m_ui->SetAmmo1Type(weapon->GetAmmoType1());
	m_ui->SetAmmo0(weapon->GetTotalAmmo0());
	m_ui->SetAmmo1(weapon->GetTotalAmmo1());
	m_ui->SetHP(Player::GetInstance()->HP);
}
