#include "stdafx.h"
#include "Hands.h"

#include "Revolver.h"
#include "Launcher.h"
#include "SMG.h"
#include "Chaingun.h"
#include "Bow.h"

void Hands::Awake()
{
	m_handsObject = CreateGameObjectToChild(transform);
	m_handsObject->transform->localPosition = Vec2(0, 0);

	m_handsMiddleObject = CreateGameObjectToChild(m_handsObject->transform);

	m_handsChildObject = CreateGameObjectToChild(m_handsMiddleObject->transform);

	SetupWeapons();
}

void Hands::Start()
{
	SetActiveWeapon(0);
}

void Hands::Update()
{
	ChangeWeapon();

	InputToActiveWeapon();
}

void Hands::LateUpdate()
{
	MoveHandsObject();

	RepositionHandsChildObject();
}

void Hands::SetWalkingState(bool value)
{
	m_isWalking = value;
}

void Hands::SetElaptionAccumulateScale(float value)
{
	m_elapionAccumulateScale = value;
}

void Hands::MoveHandsChildObject(const Vec3& deltaAngle)
{
	// 회전한 각도 차이만큼 손을 이동시킵니다.

	const float clampRange = 0.5f;
	Vec3 clampedDeltaAngle = deltaAngle * (1.0f / 360.0f);
	clampedDeltaAngle.x = Clamp(clampedDeltaAngle.x, -clampRange, +clampRange);
	clampedDeltaAngle.y = Clamp(clampedDeltaAngle.y, -clampRange, +clampRange);

	Vec2 localPosition = m_handsChildObject->transform->localPosition + Vec2(-clampedDeltaAngle.y, clampedDeltaAngle.x);
	localPosition.x = Clamp(localPosition.x, -0.5f, +0.5f);
	localPosition.y = Clamp(localPosition.y, -0.5f, +0.1f);
	m_handsChildObject->transform->localPosition = localPosition;
}

void Hands::SetActiveWeapon(int weaponIndex)
{
	if (weaponIndex < 0)
	{
		weaponIndex = 0;
	}

	m_weapons[weaponIndex]->OnPutIn();

	for (int i = 0; i < (int)WeaponTypes::Max; ++i)
	{
		m_weaponObjects[i]->activeSelf = false;
		m_weapons[i]->OnAttackInput(Weapon::InputType::Nothing);
		m_weapons[i]->OnSubInput(Weapon::InputType::Nothing);
		m_weapons[i]->OnReloadInput(Weapon::InputType::Nothing);
	}

	m_weaponObjects[weaponIndex]->activeSelf = true;
	m_weapons[weaponIndex]->OnChanged();

	m_activeWeaponIndex = weaponIndex;
}

void Hands::AddAmmo(WeaponTypes weapon, AmmoTypes ammo, unsigned int count)
{
	m_weapons[(unsigned int)weapon]->AddAmmo(ammo, count);
}

Weapon* Hands::GetActiveWeapon() const
{
	return m_weapons[m_activeWeaponIndex];
}

void Hands::SetupWeapons()
{
	m_weaponObjects[(unsigned int)WeaponTypes::Revolver] = CreateGameObjectToChild(m_handsChildObject->transform);
	m_weapons[(unsigned int)WeaponTypes::Revolver] = m_weaponObjects[(unsigned int)WeaponTypes::Revolver]->AddComponent<Revolver>();

	m_weaponObjects[(unsigned int)WeaponTypes::Launcher] = CreateGameObjectToChild(m_handsChildObject->transform);
	m_weapons[(unsigned int)WeaponTypes::Launcher] = m_weaponObjects[(unsigned int)WeaponTypes::Launcher]->AddComponent<Launcher>();

	m_weaponObjects[(unsigned int)WeaponTypes::SMG] = CreateGameObjectToChild(m_handsChildObject->transform);
	m_weapons[(unsigned int)WeaponTypes::SMG] = m_weaponObjects[(unsigned int)WeaponTypes::SMG]->AddComponent<SMG>();

	m_weaponObjects[(unsigned int)WeaponTypes::Chaingun] = CreateGameObjectToChild(m_handsChildObject->transform);
	m_weapons[(unsigned int)WeaponTypes::Chaingun] = m_weaponObjects[(unsigned int)WeaponTypes::Chaingun]->AddComponent<Chaingun>();

	m_weaponObjects[(unsigned int)WeaponTypes::Bow] = CreateGameObjectToChild(m_handsChildObject->transform);
	m_weapons[(unsigned int)WeaponTypes::Bow] = m_weaponObjects[(unsigned int)WeaponTypes::Bow]->AddComponent<Bow>();

	for (int i = 0; i < (int)WeaponTypes::Max; ++i)
	{
		m_weaponObjects[i]->activeSelf = false;
	}
}

void Hands::InputToActiveWeapon()
{
	using t = Weapon::InputType;
	constexpr t keydown = t::KeyDown;
	constexpr t keypressing = t::KeyPressing;
	constexpr t keyup = t::KeyUp;
	constexpr t nothing = t::Nothing;

	t attack = nothing;
	t sub = nothing;
	t reload = nothing;

	if (m_weaponChangingCounter <= 0)
	{
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
	}

	if (m_activeWeaponIndex < 0 || m_activeWeaponIndex >= (int)WeaponTypes::Max)
	{
		return;
	}

	m_weapons[m_activeWeaponIndex]->OnAttackInput(attack);
	m_weapons[m_activeWeaponIndex]->OnSubInput(sub);
	m_weapons[m_activeWeaponIndex]->OnReloadInput(reload);
}

void Hands::MoveHandsObject()
{
	if (m_isWalking)
	{
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
		// 걷지 않을 때 손 위치 변화를 원점으로 부드럽게 이동시킵니다.
		m_handsObject->transform->localPosition =
			Vec2::Lerp(m_handsObject->transform->localPosition, Vec2::zero(), Time::UnscaledDelteTime() * 20.0f);
		m_elapsed = 0;
	}
}

void Hands::RepositionHandsChildObject()
{	
	// 카메라 회전에 의한 손 위치 변화를 원점으로 부드럽게 이동시킵니다.
	m_handsChildObject->transform->localPosition = 
		Vec2::Lerp(m_handsChildObject->transform->localPosition, Vec2::zero(), Time::UnscaledDelteTime() * 10.0f);
}

void Hands::ChangeWeapon()
{
	int changeWeaponIndex = -1;
	for (int i = 0; i < (int)WeaponTypes::Max; ++i)
	{
		Key key = (Key)(i + (int)Key::One);
		if (Input::GetKeyDown(key))
		{
			changeWeaponIndex = i;
		}
	}

	if (changeWeaponIndex != m_activeWeaponIndex && changeWeaponIndex >= 0 && changeWeaponIndex < (int)WeaponTypes::Max)
	{
		m_weaponChangeIndex = changeWeaponIndex;
		m_weaponChangingCounter = 0.2f;
	}

	if (m_weaponChangingCounter > 0)
	{
		m_weaponChangingCounter -= Time::DeltaTime();

		if (m_weaponChangingCounter <= 0)
		{
			SetActiveWeapon(m_weaponChangeIndex);
		}
	}

	if (m_weaponChangingCounter > 0)
	{
		m_handsMiddleObject->transform->localPosition = 
			Vec2::Lerp(m_handsMiddleObject->transform->localPosition, m_handsMiddleHideLocalPosition, Time::DeltaTime() * 10.0f);
	}
	else
	{
		m_handsMiddleObject->transform->localPosition = 
			Vec2::Lerp(m_handsMiddleObject->transform->localPosition, m_handsMiddleShowLocalPosition, Time::DeltaTime() * 10.0f);
	}
}
