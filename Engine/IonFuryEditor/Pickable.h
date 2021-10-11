#pragma once

enum class Type { Monster, Trigger, Map, TypeEnd };
enum class Monster_Type {Monster0, Monster1, Monster2, Monster3, Monster4, MonsterEnd};	//추후 몬스터가 정해지면 수정

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
		, const wstring& localPathTexture = L"../SharedResourced/Texture/Dev.png");

	void SetMesh(COMBOBOX comboBox);
	void DeleteMesh();

	static Pickable* Pick();	//vec순환해서 

public:
	void PushInVector(Type type);

public:
	UserMeshRenderer*	GetRenderer() { return m_Renderer; }
	GameObject* GetChildObject() { return m_ChildObject; }

	Type GetType() { return m_Type; }
	COMBOBOX GetMeshType() { return m_MeshType; }
	UserMesh* GetUserMesh() {return m_Mesh; }

	//void SetMeshType(COMBOBOX Meshtype) { m_MeshType = Meshtype; }

private:
	GameObject*			m_ChildObject = nullptr;
	UserMeshRenderer*	m_Renderer = nullptr;

	UserMesh*			m_Mesh = nullptr;
	COMBOBOX			m_MeshType;

	Type				m_Type = Type::TypeEnd;
	Monster_Type		m_MonsterType = Monster_Type::MonsterEnd;

	bool				m_CollisionExistence = false;
	
public:
	static std::vector<Pickable*>	g_PickableVec;	//pick함수를 사용하기 위해 있다

	static std::vector<Pickable*>	g_MapVec;		//type::map
	static std::vector<Pickable*>	g_TriggerVec;	//type::trigger
	static std::vector<Pickable*>	g_MonsterVec;	//type::Monster을 저장로드하기 위해 있다.
};

