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

	static Pickable* Pick(float& Distance);	//vec순환해서 

public:
	void PushInVector(Type type);
	void PushInEventVector(Pickable* Event);

public:
	UserMeshRenderer* GetRenderer() { return m_Renderer; }
	GameObject* GetChildObject() { return m_ChildObject; }

	Type GetType() { return m_Type; }
	void SetType(Type type) { m_Type = type; }
	COMBOBOX GetMeshType() { return m_MeshType; }
	UserMesh* GetUserMesh() { return m_Mesh; }
	bool GetCollisionExistence() { return m_CollisionExistence; }
	void SetCollisionExistence(bool set) { m_CollisionExistence = set; }
	bool GetTriggerOnce() { return m_TriggerOnce; }
	void SetTriggerOnce(bool set) { m_TriggerOnce = set; }

	void SetNoLightTransparentMaterial();
	void DeleteMaterial();
public:
	EventType GetEventType() { return m_EventType; }
	TriggerMethod GetTriggerMethod() { return m_TriggerMethod; }
	void SetEventType(EventType type) { m_EventType = type; }
	void SetTriggerMethod(TriggerMethod method) { m_TriggerMethod = method; }
public:
	std::vector<Pickable*>&	GetEventVec() { return m_EventVec; }
	int						GetTriggerVectorIndex();
	void					GetEventVectorIndex(int& TriggerIndex, int& EventIndex);
	void					ClearEventVector();
	void					RemoveEventObject(int idx);

public:
	void					SetComponentToPickable(EventType type);
	void					RemoveCompObjectAndComponent();
	void					CreateComponentObject();
	void					SetOverSeeBlackMaterial();
private:
	GameObject*				m_ChildObject = nullptr;
	UserMeshRenderer*		m_Renderer = nullptr;

	UserMesh*				m_Mesh = nullptr;
	COMBOBOX				m_MeshType;
	Material*				m_Material = nullptr;

	GameObject*				m_ComponentObject = nullptr;

private:
	Type					m_Type = Type::TypeEnd;
	EventType				m_EventType = EventType::EventObjectEnd;
	TriggerMethod			m_TriggerMethod = TriggerMethod::End;

	bool					m_CollisionExistence = false;
	bool					m_TriggerOnce = false;

	std::vector<Pickable*>	m_EventVec;
	
public:
	static std::vector<Pickable*>	g_PickableVec;	//pick함수를 사용하기 위해 있다

	static std::vector<Pickable*>	g_MapVec;		//type::map
	static std::vector<Pickable*>	g_TriggerVec;	//type::trigger

	static void						ClearTriggerVector();
	static void						ClearMapVector();
};

