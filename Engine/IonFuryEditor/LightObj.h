#pragma once


enum class LIGHT {AMBINENT, DIRECTIONAL, POINT, SPOT, END};

class LightObj :  public Component
{
public:

	// 정석 컴포넌트의 선언부분입니다.
	DeclareStaticComponent(LightObj);

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

public:
	void LightSettings(const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh");

	static LightObj* LightPick();

	void AddLightObject();


public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:
	LIGHT m_LightType;		// enum 
	
	GameObject* m_LightChildObject; //addcomponet 로 타입을 넣어주면된다. 

	UserMeshRenderer* m_LightRenderer;

public:
	static std::vector<LightObj*> g_vecLight;


};

