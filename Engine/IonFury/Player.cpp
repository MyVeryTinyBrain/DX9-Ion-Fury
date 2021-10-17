#include "stdafx.h"
#include "Player.h"
#include "FPSCharacterController.h"
#include "FPSCamera.h"
#include "FPSOrthoCamera.h"
#include "Hands.h"
#include "PlayerUI.h"

ImplementStaticComponent(Player);

void Player::Awake()
{
	g_instance = this;

	m_controller = gameObject->AddComponent<FPSCharacterController>();
}

void Player::Update()
{
	if (Input::GetKeyDown(Key::Up))
	{
		AddHP(1);
	}
	if (Input::GetKeyDown(Key::Down))
	{
		SubtractHP(1);
	}
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

void Player::AddAmmo(WeaponTypes weapon, AmmoTypes ammo, unsigned int count)
{
	m_controller->fpsCamera->fpsOrthoCamera->hands->AddAmmo(weapon, ammo, count);
}
