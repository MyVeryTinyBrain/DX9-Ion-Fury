#pragma once

class Item : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(Update);

protected:

	virtual wstring InitTextureLocalPath() const = 0;

	virtual void OnTrigger(class Player* player) = 0;

private:

	GameObject* m_root = nullptr;

	UserMeshBillboardRenderer* m_renderer = nullptr;

	float m_triggerRadius = 0.5f;

	UserMeshRenderer* m_debugRenderer = nullptr;
};

