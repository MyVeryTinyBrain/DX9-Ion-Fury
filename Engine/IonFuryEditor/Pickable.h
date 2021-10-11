#pragma once

enum class Type { Monster, Trigger, Map, TypeEnd };
enum class Monster_Type {Monster0, Monster1, Monster2, Monster3, Monster4, MonsterEnd};	//추후 몬스터가 정해지면 수정

class Pickable : public Component
{
public:
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);
public:
	void Settings(bool ColliderExistence
		, const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh"
		, const wstring& localPathTexture = L"../SharedResourced/Texture/Dev.png");

	static Pickable* Pick();	//vec순환해서 

public:
	void PushInVector(Type type);

public:
	UserMeshRenderer*	GetRenderer() { return m_Renderer; }
	GameObject* GetChildObject() { return m_ChildObject; }

	Type GetType() { return m_Type; }
	bool GetColliderExistence() { return m_ColliderExistence; }

	void SetType(Type type) { m_Type = type; }
	void SetColliderExistence(bool set) { m_ColliderExistence = set; }

private:
	GameObject*			m_ChildObject;
	UserMeshRenderer*	m_Renderer;
	Type				m_Type = Type::TypeEnd;
	Monster_Type		m_MonsterType = Monster_Type::MonsterEnd;

	bool				m_ColliderExistence = false;
	
public:
	static std::vector<Pickable*>	g_PickableVec;	//pick함수를 사용하기 위해 있다

	static std::vector<Pickable*>	g_MapVec;		//type::map
	static std::vector<Pickable*>	g_TriggerVec;	//type::trigger
	static std::vector<Pickable*>	g_MonsterVec;	//type::Monster을 저장로드하기 위해 있다.
};

