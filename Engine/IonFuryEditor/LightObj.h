#pragma once


enum class LIGHT {AMBINENT, DIRECTIONAL, POINT, SPOT, END};


class LightObj :  public Component
{
public:

	// ���� ������Ʈ�� ����κ��Դϴ�.
	DeclareStaticComponent(LightObj);

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

public:
	void LightSettings(const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh");

	static LightObj* LightPick();

public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

	//void AddLight(const tag_t& tag = L"Light",
	//	const wstring& LightName = L"DefaultName",
	//	const wstring& localPathMesh = BuiltInCubeUserMesh);



private:
	LIGHT m_LightType;
	
	GameObject* m_LightChildObject;

	UserMeshRenderer* m_LightRenderer;


public:
	static std::vector<LightObj*> g_LightVec;
};

