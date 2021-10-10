#pragma once


enum class LIGHT {AMBINENT, DIRECTIONAL, POINT, SPOT, END};

class LightObj :  public Component
{
public:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

public:
	void LightSettings(const wstring& localPathMesh = BuiltInCubeUserMesh
		, const wstring& localPathTexture = L"../SharedResource/Texture/Dev.png");

	static LightObj* LightPick();

	void RequireDestroy();

public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:
	LIGHT m_LightType = LIGHT::END;		// enum 
	
	GameObject* m_LightChildObject; //addcomponet 로 타입을 넣어주면된다. 

	UserMeshRenderer* m_LightRenderer;


public:
	static std::vector<LightObj*> g_vecLight;

private:
	bool m_destroyRequire = false;
};

