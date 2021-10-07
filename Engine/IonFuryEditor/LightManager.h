#pragma once


enum class LIGHT {AMBINENT, DIRECTIONAL, POINT, SPOT, END};
class LightObject;

class LightManager :  public Component
{
public:

	// 정석 컴포넌트의 선언부분입니다.
	DeclareStaticComponent(LightManager);

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);


	static LightManager* LightPick();

public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

public:

	void AddLight(const tag_t& tag = L"Light", 
		const wstring& LightName = L"DefaultName", 
		const wstring& localPathMesh = BuiltInCubeUserMesh);

	UserMeshRenderer* m_LightRenderer;


public:
	//여기서 추가해서 관리하는것
	static std::vector<LightObject*> g_LightVec;
};

