#include "stdafx.h"
#include "FPSOrthoCamera.h"
#include "RenderLayers.h"
#include "Revolver.h"

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
	}

	m_handsObject = CreateGameObjectToChild(m_forwardGameObject->transform);
	m_handsObject->transform->localPosition = Vec2(0, 0);

	m_handsChildObject = CreateGameObjectToChild(m_handsObject->transform);

	SetupWeapons();
}

void FPSOrthoCamera::Update()
{
	InputToActiveWeapon();
}

void FPSOrthoCamera::LateUpdate()
{
	MoveHandsObject();

	RepositionHandsChildObject();
}

Camera* FPSOrthoCamera::GetCamera() const
{
	return m_camera;
}

Transform* FPSOrthoCamera::GetForwardTransform() const
{
	return m_forwardGameObject->transform;
}

void FPSOrthoCamera::MoveHandsChildObject(const Vec3& deltaAngle)
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

void FPSOrthoCamera::SetElaptionAccumulateScale(float value)
{
	m_elapionAccumulateScale = value;
}

void FPSOrthoCamera::SetCrossHair(bool value)
{
	m_crosshairRenderer->gameObject->activeSelf = value;
}

void FPSOrthoCamera::SetActiveWeapon(unsigned int weaponIndex)
{
	for (int i = 0; i < (int)WeaponTypes::Max; ++i)
	{
		m_weaponObjects[i]->activeSelf = false;
	}

	m_weaponObjects[weaponIndex]->activeSelf = true;
	m_weapons[weaponIndex]->OnChanged();
}

void FPSOrthoCamera::SetupWeapons()
{
	m_weaponObjects[(unsigned int)WeaponTypes::Revolver] = CreateGameObjectToChild(m_handsChildObject->transform);
	m_weapons[(unsigned int)WeaponTypes::Revolver] = m_weaponObjects[(unsigned int)WeaponTypes::Revolver]->AddComponent<Revolver>();

	for (int i = 0; i < (int)WeaponTypes::Max; ++i)
	{
		m_weaponObjects[i]->activeSelf = false;
	}

	SetActiveWeapon(0);
}

void FPSOrthoCamera::InputToActiveWeapon()
{
	using t = Weapon::InputType;
	constexpr t keydown = t::KeyDown;
	constexpr t keypressing = t::KeyPressing;
	constexpr t keyup = t::KeyUp;
	constexpr t nothing = t::Nothing;

	t attack = nothing;
	t sub = nothing;
	t reload = nothing;

	if (Input::GetKeyDown(Key::LeftMouse))
	{
		attack = keydown;
	}
	else if (Input::GetKey(Key::LeftMouse))
	{
		attack = keypressing;
	}
	else if (Input::GetKeyUp(Key::LeftMouse))
	{
		attack = keyup;
	}

	if (Input::GetKeyDown(Key::RightMouse))
	{
		sub = keydown;
	}
	else if (Input::GetKey(Key::RightMouse))
	{
		sub = keypressing;
	}
	else if (Input::GetKeyUp(Key::RightMouse))
	{
		sub = keyup;
	}

	if (Input::GetKeyDown(Key::R))
	{
		reload = keydown;
	}
	else if (Input::GetKey(Key::R))
	{
		reload = keypressing;
	}
	else if (Input::GetKeyUp(Key::R))
	{
		reload = keyup;
	}

	m_weapons[m_activeWeaponIndex]->OnAttackInput(attack);
	m_weapons[m_activeWeaponIndex]->OnSubInput(sub);
	m_weapons[m_activeWeaponIndex]->OnReloadInput(reload);
}

void FPSOrthoCamera::MoveHandsObject()
{
	if (m_isWalking)
	{
		//const float t = m_elapsed * 5.0f;
		//float funcX = sinf(t - PI * 0.5f) + 1.0f;
		//float funcY = -powf(funcX - 1.0f, 2.0f) + 1.0f;
		//m_handsObject->transform->localPosition = Vec2(funcX, funcY * 0.5f) * 0.05f;

		const float t = m_elapsed * 7.5f;
		float f = sinf(t);
		float g = -pow(f, 2.0f);
		m_handsObject->transform->localPosition = Vec2(f, g * 0.5f) * 0.05f;

		m_elapsed += Time::DeltaTime() * m_elapionAccumulateScale;
		m_isWalking = false;
		m_elapionAccumulateScale = 1.0f;
	}
	else
	{
		m_handsObject->transform->localPosition = Vec2::Lerp(m_handsObject->transform->localPosition, Vec2::zero(), Time::UnscaledDelteTime() * 10.0f);
		m_elapsed = 0;
	}
}

void FPSOrthoCamera::RepositionHandsChildObject()
{
	m_handsChildObject->transform->localPosition = Vec2::Lerp(m_handsChildObject->transform->localPosition, Vec2::zero(), Time::UnscaledDelteTime() * 10.0f);
}
