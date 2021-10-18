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
	UserMeshRenderer* GetRenderer() { return m_Renderer; }
public:
	void AddTypeToChildObject(CString Type);
public:
	static HandlingObject* Pick(float& Distance);
private:
	GameObject*			m_ChildObject = nullptr;
	UserMeshRenderer*	m_Renderer = nullptr;
	Material*			m_Material = nullptr;

	CString				m_HandlingObjectType = L"";
public:
	static std::vector<HandlingObject*> g_HandlingVec;
};

