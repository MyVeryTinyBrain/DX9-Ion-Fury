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

	static Pickable* Pick();	//vec��ȯ�ؼ� 
	//static void PickDelete();	//gizmo�پ��ִ� �༮�� ����


public:
	UserMeshRenderer* GetRenderer() { return m_Renderer; }

private:
	GameObject* m_ChildObject;
	UserMeshRenderer* m_Renderer;

public:
	static std::vector<Pickable*>	g_PickableVec;
};

