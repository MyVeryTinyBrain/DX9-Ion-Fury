#include "stdafx.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "FPSOrthoCamera.h"
#include "Hands.h"

ImplementStaticComponent(Player);

void Player::Awake()
{
	g_instance = this;

	m_controller = gameObject->AddComponent<FPSCharacterController>();
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

void Player::AddHP(int hp)
{
	m_hp += hp;

	if (m_hp > 100)
	{
		m_hp = 100;
	}
}

void Player::SetHP(int hp)
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

void Player::AddAmmo(WeaponTypes weapon, AmmoTypes ammo, unsigned int count)
{
	m_controller->fpsCamera->fpsOrthoCamera->hands->AddAmmo(weapon, ammo, count);
}
