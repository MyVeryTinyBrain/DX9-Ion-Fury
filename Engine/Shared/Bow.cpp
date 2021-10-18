#include "shared_stdafx.h"
#include "Bow.h"
#include "RenderLayers.h"
#include "OverlayRenderOrders.h"
#include "BowAnimator.h"
#include "Arrow.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "OrthoEffect.h"

void Bow::Awake()
{
	Weapon::Awake();

	m_bodyObj = CreateGameObjectToChild(transform);

	m_bowObj = CreateGameObjectToChild(m_bodyObj->transform);

	m_stringEffectObj = CreateGameObjectToChild(m_bowObj->transform);

	m_screenObj = CreateGameObjectToChild(m_bowObj->transform);

	m_screenTexture[0] = nullptr;
	m_screenTexture[1] = Resource::FindAs<Texture>(L"../SharedResource/Texture/bow_screen/1.png");
	m_screenTexture[2] = Resource::FindAs<Texture>(L"../SharedResource/Texture/bow_screen/2.png");
	m_screenTexture[3] = Resource::FindAs<Texture>(L"../SharedResource/Texture/bow_screen/3.png");
	m_screenTexture[4] = Resource::FindAs<Texture>(L"../SharedResource/Texture/bow_screen/4.png");
	m_screenTexture[5] = Resource::FindAs<Texture>(L"../SharedResource/Texture/bow_screen/5.png");

	// 렌더러 생성 및 설정
	m_bowRenderer = m_bowObj->AddComponent<UserMeshRenderer>();
	m_bowRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_bowRenderer->material = Resource::FindAs<Material>(BuiltInLightOverlayMaterial);
	m_bowRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_bowRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerWeaponOverlay1);

	m_screenRenderer = m_screenObj->AddComponent<UserMeshRenderer>();
	m_screenRenderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_screenRenderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_screenRenderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);
	m_screenRenderer->overlayRenderOrder = int(OverlayRenderOrders::PlayerWeaponOverlay2);

	// 애니메이터 부착
	m_bowAnimator = m_bowObj->AddComponent<BowAnimator>();
	m_bowAnimator->OnShoot += Function<void()>(this, &Bow::OnShoot);
	m_bowAnimator->OnReloaded += Function<void()>(this, &Bow::OnReloaded);

	// 평면의 크기와 그에 따른 위치 조절
	m_bodyObj->transform->localScale = Vec2(2, 2);
	m_bodyObj->transform->localPosition = Vec2(-0.25f, 0.45f);
}

void Bow::Update()
{
	Weapon::Update();

	if (m_loadedAmmo == 0)
	{
		TryReload();
	}

	if (m_shootCounter > 0)
	{
		m_shootCounter -= Time::DeltaTime();
	}

	m_screenRenderer->enable = 
		(m_bowAnimator->IsPlayingIdle() || m_bowAnimator->IsPlayingPullString()) &&
		m_screenRenderer->GetTexture(0).IsNull() == false;

	float ammoPercent = float(m_loadedAmmo) / float(m_ammoLoadMax);
	SetScreen(int(ammoPercent * 5.0f));
}

void Bow::OnDestroy()
{
	Weapon::OnDestroy();
}

void Bow::OnChanged()
{
	Player::GetInstance()->perspectiveCamera->fov = 90.0f;

	m_bowObj->transform->localPosition = Vec2(0, 0.0f);

	m_bowAnimator->PlayIdle();

	SetScreen(1);
}

void Bow::OnPutIn()
{
}

void Bow::OnAttackInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing &&
		m_shootCounter <= 0 &&
		m_bowAnimator->IsPlayingIdle() &&
		m_loadedAmmo > 0)
	{
		m_bowAnimator->PlayShoot();

		MakeFireEffect();

		Attack();

		--m_loadedAmmo;

		float randomAngle = float(rand() % 20 - 10) + 90.0f;
		Player::GetInstance()->controller->fpsCamera->MakeRecoil(Vec2::Direction(randomAngle) * 2.0f, 0.25f, 4.0f);

		m_shootCounter = m_shootDelay;
	}
}

void Bow::OnSubInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing && 
		m_bowAnimator->IsPlayingReload() == false)
	{
		Player::GetInstance()->perspectiveCamera->fov = 
			MathEx::Lerp(Player::GetInstance()->perspectiveCamera->fov, 50.0f, Time::DeltaTime() * 10.0f);

		m_bowObj->transform->localPosition =
			Vec2::Lerp(m_bowObj->transform->localPosition, Vec2(0.05f, -0.06f), Time::DeltaTime() * 10.0f);
	}
	else
	{
		Player::GetInstance()->perspectiveCamera->fov = 
			MathEx::Lerp(Player::GetInstance()->perspectiveCamera->fov, 90.0f, Time::DeltaTime() * 10.0f);

		m_bowObj->transform->localPosition =
			Vec2::Lerp(m_bowObj->transform->localPosition, Vec2(0, 0.0f), Time::DeltaTime() * 10.0f);
	}
}

void Bow::OnReloadInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		TryReload();
	}
}

AmmoTypes Bow::GetAmmoType0() const
{
	return AmmoTypes::Arrow;
}

AmmoTypes Bow::GetAmmoType1() const
{
	return AmmoTypes::None;
}

unsigned int Bow::GetTotalAmmo0() const
{
	return m_totalAmmo;
}

unsigned int Bow::GetTotalAmmo1() const
{
	return 0;
}

unsigned int Bow::GetLoadedAmmo0() const
{
	return m_loadedAmmo;
}

unsigned int Bow::GetLoadedAmmo1() const
{
	return 0;
}

bool Bow::GetLoadedAmmo0State() const
{
	return true;
}

bool Bow::GetLoadedAmmo1State() const
{
	return false;
}

void Bow::AddAmmo(AmmoTypes ammo, unsigned int count)
{
	m_totalAmmo += count;

	if (m_totalAmmo > 999)
	{
		m_totalAmmo = 999;
	}
}

void Bow::OnShoot()
{
}

void Bow::OnReloaded()
{
	int emptyAmmos = (int)Abs(m_ammoLoadMax - m_loadedAmmo);
	int reloadableAmmos = (int)Clamp(emptyAmmos, 0, m_totalAmmo);
	m_loadedAmmo += reloadableAmmos;
	m_totalAmmo -= reloadableAmmos;
}

void Bow::TryReload()
{
	if (m_bowAnimator->IsPlayingIdle() &&
		m_totalAmmo > 0 &&
		m_loadedAmmo < m_ammoLoadMax)
	{
		m_bowAnimator->PlayReload();
	}
}

void Bow::Attack()
{
	GameObject* arrowObj = CreateGameObject();
	arrowObj->transform->position = 
		Player::GetInstance()->perspectiveCamera->transform->position + Player::GetInstance()->perspectiveCamera->transform->forward * 0.5f;
	arrowObj->transform->forward = Player::GetInstance()->perspectiveCamera->transform->forward;

	Arrow* arrow = arrowObj->AddComponent<Arrow>();
	arrow->rigidbody->velocity = arrow->transform->forward * 50;
}

void Bow::SetScreen(int value)
{
	if (value < 0)
	{
		value = 0;
	}

	if (value >= 6)
	{
		value = 5;
	}

	m_screenRenderer->SetTexture(0, m_screenTexture[value]);
}

void Bow::MakeFireEffect()
{
	auto effectObj = CreateGameObjectToChild(m_bowObj->transform);
	effectObj->transform->localPosition = Vec2(0.22f, -0.32f);
	effectObj->transform->localScale = Vec2::one() * 0.2f;
	auto effect = effectObj->AddComponent<OrthoEffect>();
	effect->SetInterval(0.005f);

	int index0 = rand() % 9;
	int index1 = rand() % 9;
	int index2 = rand() % 9;

	wchar_t buffer0[256];
	swprintf_s(buffer0, L"../SharedResource/Texture/bow_effect/%d.png", index0);

	wchar_t buffer1[256];
	swprintf_s(buffer1, L"../SharedResource/Texture/bow_effect/%d.png", index1);

	wchar_t buffer2[256];
	swprintf_s(buffer2, L"../SharedResource/Texture/bow_effect/%d.png", index2);

	effect->AddTexture(buffer0);
	effect->AddTexture(buffer1);
	effect->AddTexture(buffer2);
}
