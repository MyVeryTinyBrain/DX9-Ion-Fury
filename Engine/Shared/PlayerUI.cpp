#include "shared_stdafx.h"
#include "PlayerUI.h"
#include "Numbers.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"

void PlayerUI::Awake()
{
	// Player face
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

	// HP Numbers
	m_hpObj = CreateGameObjectToChild(transform);
	m_hpObj->transform->localPosition = Vec2(-0.71f, -0.45f);
	m_hpObj->transform->localScale = Vec2::one() * 0.05f;
	m_hpNumbers = m_hpObj->AddComponent<Numbers>();

	// Armor Image
	m_armorImageObj = CreateGameObjectToChild(transform);
	m_armorImageObj->transform->localPosition = Vec2(-0.54f, -0.44f);
	m_armorImageObj->transform->localScale = Vec2::one() * 0.125f;

	Texture* armorImageTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/item/armor.png");
	m_armorImageRenderer = m_armorImageObj->AddComponent<UserMeshRenderer>();
	m_armorImageRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_armorImageRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_armorImageRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_armorImageRenderer->overlayRenderOrder = (int)OverlayRenderOrders::UIPic;
	m_armorImageRenderer->SetTexture(0, armorImageTexture);

	// Armor Numbers
	m_armorObj = CreateGameObjectToChild(transform);
	m_armorObj->transform->localPosition = Vec2(-0.41f, -0.45f);
	m_armorObj->transform->localScale = Vec2::one() * 0.05f;
	m_armorNumbers = m_armorObj->AddComponent<Numbers>();

	// Cardkey
	m_cardKeyObj = CreateGameObjectToChild(transform);
	m_cardKeyObj->transform->localPosition = Vec2(-0.83f, -0.34f);
	m_cardKeyObj->transform->localScale = Vec2::one() * 0.1f;
	m_cardKeyRenderer = m_cardKeyObj->AddComponent<UserMeshRenderer>();
	m_cardKeyRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_cardKeyRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_cardKeyRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_cardKeyRenderer->overlayRenderOrder = (int)OverlayRenderOrders::UIPic;
	m_cardKeyRenderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/item/card.png"));
	m_cardKeyObj->activeSelf = false;

	// Ammo0 Numbers
	m_ammoObj0 = CreateGameObjectToChild(transform);
	m_ammoObj0->transform->localPosition = Vec2(0.69f, -0.45f);
	m_ammoObj0->transform->localScale = Vec2::one() * 0.05f;
	m_ammoNumbers0 = m_ammoObj0->AddComponent<Numbers>();
	m_ammoNumbers0->alignment = Numbers::Alignment::Right;

	// Loaded Ammo0 Numbers
	m_loadedAmmoObj0 = CreateGameObjectToChild(transform);
	m_loadedAmmoObj0->transform->localPosition = Vec2(0.50f, -0.45f);
	m_loadedAmmoObj0->transform->localScale = Vec2::one() * 0.05f;
	m_loadedAmmoNumbers0 = m_loadedAmmoObj0->AddComponent<Numbers>();
	m_loadedAmmoNumbers0->alignment = Numbers::Alignment::Right;

	// Ammo1 Numbers
	m_ammoObj1 = CreateGameObjectToChild(transform);
	m_ammoObj1->transform->localPosition = Vec2(0.69f, -0.35f);
	m_ammoObj1->transform->localScale = Vec2::one() * 0.05f;
	m_ammoNumbers1 = m_ammoObj1->AddComponent<Numbers>();
	m_ammoNumbers1->alignment = Numbers::Alignment::Right;

	// Loaded Ammo1 Numbers
	m_loadedAmmoObj1 = CreateGameObjectToChild(transform);
	m_loadedAmmoObj1->transform->localPosition = Vec2(0.50f, -0.35f);
	m_loadedAmmoObj1->transform->localScale = Vec2::one() * 0.05f;
	m_loadedAmmoNumbers1 = m_loadedAmmoObj1->AddComponent<Numbers>();
	m_loadedAmmoNumbers1->alignment = Numbers::Alignment::Right;

	// Ammo0 type image
	m_ammoTypeObj0 = CreateGameObjectToChild(transform);
	m_ammoTypeObj0->transform->localPosition = Vec2(0.825f, -0.44f);
	m_ammoTypeObj0->transform->localScale = Vec2::one() * 0.081f;
	m_ammoTypeRenderer0 = m_ammoTypeObj0->AddComponent<UserMeshRenderer>();
	m_ammoTypeRenderer0->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_ammoTypeRenderer0->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_ammoTypeRenderer0->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_ammoTypeRenderer0->overlayRenderOrder = (int)OverlayRenderOrders::UIPic;

	// Ammo1 type image
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

	// Screen Effect
	m_redScreenEffectTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/screeneffect/red.png");;
	m_greenScreenEffectTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/screeneffect/green.png");
	m_blueScreenEffectTexture = Resource::FindAs<Texture>(L"../SharedResource/Texture/screeneffect/blue.png");

	m_screenEffectObj = CreateGameObjectToChild(transform);
	m_screenEffectObj->transform->localScale = Vec2(Camera::GetMainCamera()->GetAspect(), 1.0f);
	m_screenEffectRenderer = m_screenEffectObj->AddComponent<UserMeshRenderer>();
	m_screenEffectRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_screenEffectRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_screenEffectRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_screenEffectRenderer->overlayRenderOrder = (int)OverlayRenderOrders::UIForeground;
	m_screenEffectRenderer->enable = false;

	// Fade effect
	for (int i = 0; i < FADE_MAX; ++i)
	{
		float percent = float(i) / float(FADE_MAX - 1);
		m_fadeTexture[i] = Texture::CreateUnmanagedInDirectX(16, 16, Color(0, 0, 0, percent));
	}

	m_fadeImageObj = CreateGameObjectToChild(transform);
	m_fadeImageObj->transform->localScale = Vec2(Camera::GetMainCamera()->GetOrthographicWidth(), 1);

	m_fadeImageRenderer = m_fadeImageObj->AddComponent<UserMeshRenderer>();
	m_fadeImageRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_fadeImageRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_fadeImageRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_fadeImageRenderer->overlayRenderOrder = (int)OverlayRenderOrders::Fade;
	m_fadeImageRenderer->SetTexture(0, m_fadeTexture[0]);

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

void PlayerUI::LateUpdate()
{
	if (Input::GetKeyDown(Key::Up))
		m_targetFadeAlpha = 1.0f;
	if (Input::GetKeyDown(Key::Down))
		m_targetFadeAlpha = 0.0f;

	// Fade effect =====================================================================

	// Fade Transition
	if (m_fadeAlpha != m_targetFadeAlpha)
	{
		if (m_fadeAlpha < m_targetFadeAlpha)
		{
			m_fadeAlpha += Time::DeltaTime() * m_fadeSpeed;

			if (m_fadeAlpha >= m_targetFadeAlpha)
			{
				m_fadeAlpha = m_targetFadeAlpha;
			}
		}
		else
		{
			m_fadeAlpha -= Time::DeltaTime() * m_fadeSpeed;
		
			if (m_fadeAlpha <= m_targetFadeAlpha)
			{
				m_fadeAlpha = m_targetFadeAlpha;
			}
		}
	}

	// Fade texture change
	float fFadeIndex = m_fadeAlpha * float(FADE_END);
	int fadeIndex = int(fFadeIndex);

	m_fadeImageRenderer->SetTexture(0, m_fadeTexture[fadeIndex]);

	if (fadeIndex == 0)
	{
		m_fadeImageRenderer->enable = false;
	}
	else
	{
		m_fadeImageRenderer->enable = true;
	}

	// Fade effect =====================================================================
}

void PlayerUI::OnDestroy()
{
	for (int i = 0; i < FADE_MAX; ++i)
	{
		if (m_fadeTexture[i])
		{
			m_fadeTexture[i]->ReleaseUnmanaged();
			m_fadeTexture[i] = nullptr;
		}
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

void PlayerUI::ShowBlueScreenEffect()
{
	m_screenEffectRenderer->SetTexture(0, m_blueScreenEffectTexture);
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

void PlayerUI::SetArmor(unsigned int value)
{
	if (value > 100)
	{
		value = 100;
	}

	if (value == 0)
	{
		m_armorNumbers->gameObject->activeSelf = false;
		m_armorImageRenderer->gameObject->activeSelf = false;
	}
	else
	{
		m_armorNumbers->gameObject->activeSelf = true;
		m_armorImageRenderer->gameObject->activeSelf = true;
	}

	m_armorNumbers->number = value;
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

void PlayerUI::SetCardKey(bool value)
{
	m_cardKeyObj->activeSelf = value;
}
