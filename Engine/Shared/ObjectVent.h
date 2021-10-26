#pragma once

#include "IUsable.h"
#include "IDontDeactive.h"

class ObjectVent : public Component, public IUsable, public IDontDeactive
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	virtual void OnUse(bool valid) override;

	virtual void OnDisable() override;

private:

	GameObject* m_root = nullptr;

	GameObject* m_fanObj = nullptr;
	
	BoxCollider* m_forceTrigger = nullptr;

	bool m_spin = true;
};

