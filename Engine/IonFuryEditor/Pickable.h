#pragma once

class Pickable : public Component
{
public:
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);
public:

	void Settings(const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh"
		, const wstring& localPathTexture = L"../SharedResourced/Texture/Dev.png");

	static Pickable* Pick();	//vec순환해서 
	//static void PickDelete();	//gizmo붙어있는 녀석은 삭제

public:
	UserMeshRenderer*	GetRenderer() { return m_Renderer; }
	GameObject* GetChildObject() { return m_ChildObject; }

private:
	GameObject* m_ChildObject;
	UserMeshRenderer* m_Renderer;

public:
	static std::vector<Pickable*>	g_PickableVec;
};

