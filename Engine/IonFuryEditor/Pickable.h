#pragma once

#include "EditorEnum.h"

class Pickable : public Component
{
public:
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);
public:
	void Settings(Vec2 UVScale
		, COMBOBOX comboBox = COMBOBOX::Cube
		, const wstring& localPathTexture = L"../SharedResourced/Texture/Dev.png"
		, bool ColliderExistence = false);

	void SetMesh(COMBOBOX comboBox);
	void DeleteMesh();

	static Pickable* Pick();	//vec순환해서 

public:
	void PushInVector(Type type);

public:
	UserMeshRenderer* GetRenderer() { return m_Renderer; }
	GameObject* GetChildObject() { return m_ChildObject; }

	Type GetType() { return m_Type; }
	COMBOBOX GetMeshType() { return m_MeshType; }
	UserMesh* GetUserMesh() { return m_Mesh; }
	bool GetCollisionExistence() { return m_CollisionExistence; }
	void SetCollisionExistence(bool set) { m_CollisionExistence = set; }

public:
	std::vector<Pickable*>	GetObtainedMonsters() { return m_ObtainedEventObjects; }
	int						GetTriggerVectorIndex();

private:
	GameObject*				m_ChildObject = nullptr;
	UserMeshRenderer*		m_Renderer = nullptr;

	UserMesh*				m_Mesh = nullptr;
	COMBOBOX				m_MeshType;

public:
	Type					m_Type = Type::TypeEnd;
	EventObjects			m_EventObjectType = EventObjects::EventObjectEnd;

	bool					m_CollisionExistence = false;

	std::vector<Pickable*>	m_ObtainedEventObjects;
	
public:
	static std::vector<Pickable*>	g_PickableVec;	//pick함수를 사용하기 위해 있다

	static std::vector<Pickable*>	g_MapVec;		//type::map
	static std::vector<Pickable*>	g_TriggerVec;	//type::trigger
	static std::vector<Pickable*>	g_EventVec;	//type::EventObj을 저장로드하기 위해 있다.
};

