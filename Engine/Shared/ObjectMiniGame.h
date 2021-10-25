#pragma once

#include "IDontDeactive.h"
#include "IUsable.h"
#include "Component.h"
#include "Texture.h"

class ObjectMiniGame : public Component, public IUsable, public IDontDeactive
{
public:
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	virtual void OnUse(bool valid) override;

	void Activate();

private:

	GameObject* m_root = nullptr;

	class Cube* m_cube = nullptr;

	Texture* m_defaultTexture = nullptr;

	Texture* m_deniedTexture = nullptr;

	Texture* m_acceptTexture = nullptr;

	Texture* m_sideTexture = nullptr;

	float m_changeAccumulate = 0.0f;

	GameObject* m_MiniGame;
};

