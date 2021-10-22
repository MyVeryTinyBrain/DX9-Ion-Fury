#pragma once

#include "EditorEnum.h"

class Trigger : public Component
{

private:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	void SetTriggerOnce(bool value);

	void SetMethod(TriggerMethod value);

	void AddSubordinationComponent(Component* value);

	void ActiveAllGameObjects();

	void Use();

	const std::vector<Ref<Component>>& GetConnections() const;

	TriggerMethod GetMethod() const;

private:

	UserMeshRenderer* m_debugRenderer = nullptr;

	TriggerMethod m_method = TriggerMethod::End;

	std::vector<Ref<Component>> m_connected;

	bool m_once = false;

	bool m_used = false;

	// For button

	Rigidbody* m_body = nullptr;

	BoxCollider* m_trigger = nullptr;

public:

	Delegate<void()> OnTrigger;
};

