#include "stdafx.h"
#include "Player.h"
#include "FPSCharacterController.h"

ImplementStaticComponent(Player);

void Player::Awake()
{
	g_instance = this;

	m_controller = gameObject->AddComponent<FPSCharacterController>();
}
