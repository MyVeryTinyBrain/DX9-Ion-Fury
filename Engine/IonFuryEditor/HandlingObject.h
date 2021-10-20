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
	GameObject* GetPivotObject() { return m_PivotObject; }
	GameObject* GetChildObject() { return m_ChildObject; }
	UserMeshRenderer* GetRenderer() { return m_Renderer; }
public:
	CString GetComponentType() { return m_ComponentType.GetString(); }
	Component* GetHandlingComponent();
	void AddComponentToChildObject(CString Type);
	void RemoveChildObjectAndComponent();
public:
	static HandlingObject* Pick(float& Distance);
	int GetHandlingVectorIndex();
public:
	static void ClearVector();
private:
	GameObject*			m_PivotObject = nullptr;
	GameObject*			m_ChildObject = nullptr;
	UserMeshRenderer*	m_Renderer = nullptr;
	Material*			m_Material = nullptr;

	CString				m_ComponentType = L"";
public:
	static std::vector<HandlingObject*> g_HandlingVec;
};

