#pragma once

class FPSCharacterController;

class Player : public Component
{
	DeclareStaticComponent(Player);

	OverrideComponentFunction(Awake);

private:

	FPSCharacterController* m_controller = nullptr;
};

