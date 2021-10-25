#pragma once

class ObjectVent : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

private:

	GameObject* m_root = nullptr;

	GameObject* m_fanObj = nullptr;
	
	BoxCollider* m_forceTrigger = nullptr;

	bool m_spin = true;
};

