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
	GameObject* GetChildObject() { return m_ChildObject; }
public:
	void AddTypeToChildObject(CString Type);
private:
	GameObject*			m_ChildObject = nullptr;
	UserMeshRenderer*	m_Renderer = nullptr;
	Material*			m_Material = nullptr;

	CString				m_HandlingObjectType = L"";
public:
	static std::vector<HandlingObject*> g_HandlingVec;
};

