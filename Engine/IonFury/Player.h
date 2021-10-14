#pragma once

class FPSCharacterController;

class Player : public Component
{
	DeclareStaticComponent(Player);

	OverrideComponentFunction(Awake);

public:

	FPSCharacterController* GetController() const;

	Camera* GetPerspectiveCamera() const;

	__declspec(property(get = GetController)) FPSCharacterController* controller;

	__declspec(property(get = GetPerspectiveCamera)) Camera* perspectiveCamera;

private:

	FPSCharacterController* m_controller = nullptr;
};

