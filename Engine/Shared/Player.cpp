#include "shared_stdafx.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "FPSOrthoCamera.h"
#include "Hands.h"
#include "PlayerUI.h"
#include "TrailRenderer.h"

ImplementStaticComponent(Player);

void Player::Awake()
{
	g_instance = this;

	m_controller = gameObject->AddComponent<FPSCharacterController>();
	gameObject->AddComponent<TrailRenderer>();
}

void Player::Update()
{
	m_controller->enable = m_rigidCounter <= 0;
	if (m_rigidCounter > 0)
	{
		m_rigidCounter -= Time::DeltaTime();
	}
}

void Player::FixedUpdate()
{
	if (m_damagedVelocity != Vec3::zero())
	{
		Vec3 velocity = m_controller->rigidbody->velocity;
		if (Abs(m_damagedVelocity.y) <= Abs(velocity.y))
		{
			m_damagedVelocity.y = 0;
		}
		velocity.x = m_damagedVelocity.x;
		velocity.z = m_damagedVelocity.z;
		if (Abs(m_damagedVelocity.y) >= 1.0f)
		{
			velocity.y = m_damagedVelocity.y;
		}
		m_controller->rigidbody->velocity = velocity;
	}
	m_damagedVelocity = Vec3::zero();
}

FPSCharacterController* Player::GetController() const
{
	return m_controller;
}

Camera* Player::GetPerspectiveCamera() const
{
	return m_controller->camera;
}

FPSCamera* Player::GetFPSCamera() const
{
	return m_controller->fpsCamera;
}

FPSOrthoCamera* Player::GetOrthoCamera() const
{
	return m_controller->fpsCamera->fpsOrthoCamera;
}

void Player::AddHP(unsigned int hp, bool effect)
{
	m_hp += hp;

	if (m_hp > 100)
	{
		m_hp = 100;
	}

	if (effect)
	{
		m_controller->fpsCamera->fpsOrthoCamera->UI->ShowGreenScreenEffect();
	}
}

void Player::SubtractHP(unsigned int hp, bool effect)
{
	if (m_hp < hp)
	{
		hp = m_hp;
	}

	m_hp -= hp;

	if (effect)
	{
		m_controller->fpsCamera->fpsOrthoCamera->UI->ShowRedScreenEffect();
	}
}

void Player::SetRigidCounter(float value)
{
	m_rigidCounter = value;
}

void Player::TakeDamage(int damage, const Vec3& velocity, float rigidTime)
{
	// ������ġ�Դϴ�.
	if (m_hp < 20)
	{
		if (damage > 1)
		{
			damage = 1;
		}
	}
	else if (m_hp < 50)
	{
		if (damage > 2)
		{
			damage = damage / 2;
		}
	}

	SubtractHP(damage);

	if (velocity.sqrMagnitude() > m_damagedVelocity.sqrMagnitude())
	{
		m_damagedVelocity = velocity;
	}

	if (m_rigidCounter < rigidTime)
	{
		SetRigidCounter(rigidTime);
	}
}

void Player::SetHP(unsigned int hp)
{
	if (hp < 0)
	{
		hp = 0;
	}

	if (hp > 100)
	{
		hp = 100;
	}

	m_hp = hp;
}

int Player::GetHP() const
{
	return m_hp;
}

void Player::AddAmmo(WeaponTypes weapon, AmmoTypes ammo, unsigned int count, bool effect)
{
	m_controller->fpsCamera->fpsOrthoCamera->hands->AddAmmo(weapon, ammo, count);

	if (effect)
	{
		m_controller->fpsCamera->fpsOrthoCamera->UI->ShowBlueScreenEffect();
	}
}