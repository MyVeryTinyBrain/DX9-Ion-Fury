#pragma once


enum class LIGHT {AMBINENT, DIRECTIONAL, POINT, SPOT, END};

class LightManager :  public Component
{
public:

	// 정석 컴포넌트의 선언부분입니다.
	DeclareStaticComponent(LightManager);

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

public:
	void LightSettings(const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh");

	static LightManager* LightPick();

public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

	void AddLight(const tag_t& tag = L"Light", 
		const wstring& LightName = L"DefaultName", 
		const wstring& localPathMesh = BuiltInCubeUserMesh);

public:

	class PointLight* GetPointLight();
	
	class SpotLight* GetSpotLight();

private:
	class PointLight* m_PointLight;

	class SpotLight* m_SpotLight;

private:
	GameObject* m_LightChildObject;

	LIGHT m_LightType;

	UserMeshRenderer* m_LightRenderer;


public:
	static std::vector<LightManager*> g_LightVec;
};

