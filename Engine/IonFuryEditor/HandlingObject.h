#pragma once

#include "EditorEnum.h"

class HandlingObject : public Component
{
public:
	OverrideComponentFunction(Awake);
	OverrideComponentFunction(OnDestroy);
public:
	void SetMaterial();
	void RemoveMaterial();
	GameObject* GetChildObject() { return m_ChildObject; };
private:
	GameObject*			m_ChildObject = nullptr;
	UserMeshRenderer*	m_Renderer = nullptr;
	Material*			m_Material = nullptr;
	ReactionType		m_ReactionType = ReactionType::End;
public:
	static std::vector<HandlingObject*> g_HandlingVec;
};

