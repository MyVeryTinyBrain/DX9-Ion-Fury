#include "stdafx.h"
#include "PlayerUI.h"
#include "Numbers.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"

void PlayerUI::Awake()
{
	m_playerFaceTexture[0] = Resource::FindAs<Texture>(L"../SharedResource/Texture/playerface/0.png");
	m_playerFaceTexture[1] = Resource::FindAs<Texture>(L"../SharedResource/Texture/playerface/1.png");
	m_playerFaceTexture[2] = Resource::FindAs<Texture>(L"../SharedResource/Texture/playerface/2.png");
	m_playerFaceTexture[3] = Resource::FindAs<Texture>(L"../SharedResource/Texture/playerface/3.png");

	m_playerFaceObj = CreateGameObjectToChild(transform);
	m_playerFaceObj->transform->localPosition = Vec2(-0.83f, -0.44f);
	m_playerFaceObj->transform->localScale = Vec2::one() * 0.125f;
	m_playerFaceRenderer = m_playerFaceObj->AddComponent<UserMeshRenderer>();
	m_playerFaceRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_playerFaceRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_playerFaceRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_playerFaceRenderer->overlayRenderOrder = (int)OverlayRenderOrders::UIPic;

	m_hpObj = CreateGameObjectToChild(transform);
	m_hpObj->transform->localPosition = Vec2(-0.71f, -0.45f);
	m_hpObj->transform->localScale = Vec2::one() * 0.05f;
	m_hpNumbers = m_hpObj->AddComponent<Numbers>();

	m_ammoObj0 = CreateGameObjectToChild(transform);
	m_ammoObj0->transform->localPosition = Vec2(0.69f, -0.45f);
	m_ammoObj0->transform->localScale = Vec2::one() * 0.05f;
	m_ammoNumbers0 = m_ammoObj0->AddComponent<Numbers>();
	m_ammoNumbers0->alignment = Numbers::Alignment::Right;

	m_loadedAmmoObj0 = CreateGameObjectToChild(transform);
	m_loadedAmmoObj0->transform->localPosition = Vec2(0.50f, -0.45f);
	m_loadedAmmoObj0->transform->localScale = Vec2::one() * 0.05f;
	m_loadedAmmoNumbers0 = m_loadedAmmoObj0->AddComponent<Numbers>();
	m_loadedAmmoNumbers0->alignment = Numbers::Alignment::Right;

	m_ammoObj1 = CreateGameObjectToChild(transform);
	m_ammoObj1->transform->localPosition = Vec2(0.69f, -0.35f);
	m_ammoObj1->transform->localScale = Vec2::one() * 0.05f;
	m_ammoNumbers1 = m_ammoObj1->AddComponent<Numbers>();
	m_ammoNumbers1->alignment = Numbers::Alignment::Right;

	m_loadedAmmoObj1 = CreateGameObjectToChild(transform);
	m_loadedAmmoObj1->transform->localPosition = Vec2(0.50f, -0.35f);
	m_loadedAmmoObj1->transform->localScale = Vec2::one() * 0.05f;
	m_loadedAmmoNumbers1 = m_loadedAmmoObj1->AddComponent<Numbers>();
	m_loadedAmmoNumbers1->alignment = Numbers::Alignment::Right;

	m_ammoTypeObj0 = CreateGameObjectToChild(transform);
	m_ammoTypeObj0->transform->localPosition = Vec2(0.825f, -0.44f);
	m_ammoTypeObj0->transform->localScale = Vec2::one() * 0.081f;
	m_ammoTypeRenderer0 = m_ammoTypeObj0->AddComponent<UserMeshRenderer>();
	m_ammoTypeRenderer0->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_ammoTypeRenderer0->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_ammoTypeRenderer0->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_ammoTypeRenderer0->overlayRenderOrder = (int)OverlayRenderOrders::UIPic;

	m_ammoTypeObj1 = CreateGameObjectToChild(transform);
	m_ammoTypeObj1->transform->localPosition = Vec2(0.825f, -0.34f);
	m_ammoTypeObj1->transform->localScale = Vec2::one() * 0.081f;
	m_ammoTypeRenderer1 = m_ammoTypeObj1->AddComponent<UserMeshRenderer>();
	m_ammoTypeRenderer1->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_ammoTypeRenderer1->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_ammoTypeRenderer1->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_ammoTypeRenderer1->overlayRenderOrder = (int)OverlayRenderOrders::UIPic;

	m_ammoTexture[(unsigned int)AmmoTypes::Revolver] = Resource::FindAs<Texture>(L"../SharedResource/Texture/item/ammo_revolver.png");
	m_ammoTexture[(unsigned int)AmmoTypes::Shotgun] = Resource::FindAs<Texture>(L"../SharedResource/Texture/item/ammo_shotgun.png");
	m_ammoTexture[(unsigned int)AmmoTypes::Launcher] = Resource::FindAs<Texture>(L"../SharedResource/Texture/item/ammo_launcher.png");
	m_ammoTexture[(unsigned int)AmmoTypes::SMG] = Resource::FindAs<Texture>(L"../SharedResource/Texture/item/ammo_smg.png");
	m_ammoTexture[(unsigned int)AmmoTypes::Chaingun] = Resource::FindAs<Texture>(L"../SharedResource/Texture/item/ammo_chaingun.png");
	m_ammoTexture[(unsigned int)AmmoTypes::Arrow] = Resource::FindAs<Texture>(L"../SharedResource/Texture/item/ammo_arrow.png");

	m_redScreenEffectTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/screeneffect/red.png");;
	m_greenScreenEffectTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/screeneffect/green.png");;

	m_screenEffectObj = CreateGameObjectToChild(transform);
	m_screenEffectObj->transform->localScale = Vec2(Camera::GetMainCamera()->GetAspect(), 1.0f);
	m_screenEffectRenderer = m_screenEffectObj->AddComponent<UserMeshRenderer>();
	m_screenEffectRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_screenEffectRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_screenEffectRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_screenEffectRenderer->overlayRenderOrder = (int)OverlayRenderOrders::UIForeground;
	m_screenEffectRenderer->enable = false;

	SetHP(100);
	SetAmmo0(999);
	SetAmmo1(999);
	SetAmmo0Type(AmmoTypes::Shotgun);
	SetAmmo1Type(AmmoTypes::Launcher);
}

void PlayerUI::Update()
{
	if (m_screenEffectObj->transform->localScale.y > 2.0f)
	{
		m_screenEffectRenderer->enable = false;
	}
	else
	{
		m_screenEffectObj->transform->localScale += Vec2::one() * 0.8f * Time::DeltaTime();
	}
}

void PlayerUI::ShowRedScreenEffect()
{
	m_screenEffectRenderer->SetTexture(0, m_redScreenEffectTexture);
	m_screenEffectRenderer->enable = true;
	m_screenEffectObj->transform->localScale = Vec2(Camera::GetMainCamera()->GetAspect(), 1);
}

void PlayerUI::ShowGreenScreenEffect()
{
	m_screenEffectRenderer->SetTexture(0, m_greenScreenEffectTexture);
	m_screenEffectRenderer->enable = true;
	m_screenEffectObj->transform->localScale = Vec2(Camera::GetMainCamera()->GetAspect(), 1);
}

void PlayerUI::SetHP(unsigned int value)
{
	if (value > 100)
	{
		value = 100;
	}

	m_hpNumbers->number = value;

	if (value > 80)
	{
		m_playerFaceRenderer->SetTexture(0, m_playerFaceTexture[0]);
	}
	else if (value > 60)
	{
		m_playerFaceRenderer->SetTexture(0, m_playerFaceTexture[1]);
	}
	else if (value > 20)
	{
		m_playerFaceRenderer->SetTexture(0, m_playerFaceTexture[2]);
	}
	else
	{
		m_playerFaceRenderer->SetTexture(0, m_playerFaceTexture[3]);
	}
}

void PlayerUI::SetLoadedAmmo0State(bool value)
{
	m_loadedAmmoObj0->activeSelf = value;
}

void PlayerUI::SetLoadedAmmo1State(bool value)
{
	m_loadedAmmoObj1->activeSelf = value;
}

void PlayerUI::SetLoadedAmmo0(unsigned int value)
{
	m_loadedAmmoNumbers0->number = value;
}

void PlayerUI::SetLoadedAmmo1(unsigned int value)
{
	m_loadedAmmoNumbers1->number = value;
}

void PlayerUI::SetAmmo0(unsigned int value)
{
	m_ammoNumbers0->number = value;
}

void PlayerUI::SetAmmo1(unsigned int value)
{
	m_ammoNumbers1->number = value;
}

void PlayerUI::SetAmmo0Type(AmmoTypes type)
{
	bool active = true;
	unsigned int index = (unsigned int)type;

	if (type == AmmoTypes::None || type == AmmoTypes::Max)
	{
		m_ammoObj0->activeSelf = false;
		m_ammoTypeObj0->activeSelf = false;
	}
	else
	{
		m_ammoTypeRenderer0->SetTexture(0, m_ammoTexture[index]);
		m_ammoObj0->activeSelf = true;
		m_ammoTypeObj0->activeSelf = true;
	}
}

void PlayerUI::SetAmmo1Type(AmmoTypes type)
{
	bool active = true;
	unsigned int index = (unsigned int)type;

	if (type == AmmoTypes::None)
	{
		m_ammoObj1->activeSelf = false;
		m_ammoTypeObj1->activeSelf = false;
	}
	else
	{
		m_ammoTypeRenderer1->SetTexture(0, m_ammoTexture[index]);
		m_ammoObj1->activeSelf = true;
		m_ammoTypeObj1->activeSelf = true;
	}
}
