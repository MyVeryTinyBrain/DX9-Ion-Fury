#pragma once

class ObjectVent : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

private:

	GameObject* m_target = nullptr;
};

