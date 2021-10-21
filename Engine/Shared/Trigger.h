#pragma once

class Trigger : public Component
{
public:

	enum class Method { Touch, Button, Manual, Max, None };

private:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	void SetTriggerOnce(bool value);

	void SetMethod(Method value);

	void AddSubordinationComponent(Component* value);

	void ActiveAllGameObjects();

	void Use();

	const std::vector<Ref<Component>>& GetConnections() const;

private:

	UserMeshRenderer* m_debugRenderer = nullptr;

	Method m_method = Method::None;

	std::vector<Ref<Component>> m_connected;

	bool m_once = false;

	bool m_used = false;

	// For button

	Rigidbody* m_body = nullptr;

	BoxCollider* m_trigger = nullptr;

public:

	Delegate<void()> OnTrigger;
};

