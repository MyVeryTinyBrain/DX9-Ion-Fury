#pragma once

#include "IDontDeactive.h"
#include "IUsable.h"

class ObjectCardScreen : public Component, public IUsable, public IDontDeactive
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	virtual void OnUse(bool valid) override;

private:

	GameObject* m_root = nullptr;

	class Cube* m_cube = nullptr;

	Texture* m_defaultTexture = nullptr;

	Texture* m_deniedTexture = nullptr;

	Texture* m_acceptTexture = nullptr;

	Texture* m_sideTexture = nullptr;

	float m_changeAccumulate = 0.0f;
};

