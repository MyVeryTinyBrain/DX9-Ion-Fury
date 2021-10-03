#pragma once

class Pickable : public Component
{
public:
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

<<<<<<< Updated upstream
=======
	OverrideComponentFunction(OnDestroy);
>>>>>>> Stashed changes
public:

	void Settings(const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh"
		, const wstring& localPathTexture = L"../SharedResourced/Texture/Dev.png");

	static Pickable* Pick(); //vec순환해서 

	UserMeshRenderer* Get_Renderer() { return m_Renderer; }

private:
	GameObject*				m_ChildObject;
	UserMeshRenderer*		m_Renderer;

	static std::vector<Pickable*>	g_PickableVec;
};

