#pragma once

#include "IDontDeactive.h"
#include "IUsable.h"

class ObjectButton : public Component, public IUsable, public IDontDeactive
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	virtual void OnUse(bool valid) override;

	GameObject* m_root = nullptr;

	class Cube* m_cube = nullptr;

	Texture* m_nonPressTexture = nullptr;

	Texture* m_pressTexture = nullptr;

	Texture* m_sideTexture = nullptr;

	float m_pressingAccumulate = 0;
};

