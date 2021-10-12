#include "stdafx.h"
#include "Revolver.h"
#include "RevolverAnimator.h"

void Revolver::Awake()
{
	Weapon::Awake();

	m_animator = m_rightHandObj->AddComponent<RevolverAnimator>();
	m_animator->OnReloaded += Function<void()>(this, &Revolver::OnReloaded);

	m_rightHandObj->transform->localPosition = Vec2(0.1f, -0.2f);

	m_rightHandLocalPositionTarget = Vec2(0.1f, -0.2f);

	m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 0);

	m_leftHandObj->activeSelf = false;

	m_animator->PlayDefaultAnimation();

	m_totalAmmo = 100;

	m_loadedAmmo = 6;

	m_ammoLoadMax = 6;
}

void Revolver::Update()
{
	Weapon::Update();

	if (m_animator->IsPlayingReloadPutin())
	{
		m_rightHandLocalPositionTarget = Vec2(0.0f, -1.0f);
		m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 45);
	}
	else
	{
		m_rightHandLocalPositionTarget = Vec2(0.1f, -0.2f);
		m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 0);
	}

	m_rightHandObj->transform->localPosition = Vec2::Lerp(m_rightHandObj->transform->localPosition, m_rightHandLocalPositionTarget, Time::DeltaTime() * 10.0f);
	m_rightHandObj->transform->localEulerAngle = Vec3::Lerp(m_rightHandObj->transform->localEulerAngle, m_rightHandLocalEulerAngleTarget, Time::DeltaTime() * 10.0f);
}

void Revolver::OnDestroy()
{
	m_animator->OnReloaded -= Function<void()>(this, &Revolver::OnReloaded);
}

void Revolver::OnChanged()
{
	m_rightHandObj->transform->localPosition = Vec2(0.1f, -0.2f);

	m_rightHandLocalPositionTarget = Vec2(0.1f, -0.2f);

	m_rightHandLocalEulerAngleTarget = Vec3(0, 0, 0);

	m_leftHandObj->activeSelf = false;

	m_animator->PlayDefaultAnimation();
}

void Revolver::OnAttackInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		if (m_animator->IsPlayingIdle() &&
			m_loadedAmmo > 0)
		{
			m_animator->PlayShoot();
			--m_loadedAmmo;
		}
	}
}

void Revolver::OnSubInput(InputType inputType)
{
}

void Revolver::OnReloadInput(InputType inputType)
{
	if (inputType == InputType::KeyPressing)
	{
		if (!m_animator->IsPlayingReload() &&
			m_totalAmmo > 0)
		{
			m_animator->PlayReload();
		}
	}
}

void Revolver::OnReloaded()
{
	m_totalAmmo -= (m_ammoLoadMax - m_loadedAmmo);
	m_loadedAmmo = Clamp(m_totalAmmo, 0, m_ammoLoadMax);
}
