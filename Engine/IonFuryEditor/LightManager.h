#pragma once


enum class LIGHT {AMBINENT, DIRECTIONAL, POINT, SPOT, END};
class LightObject;

class LightManager :  public Component
{
public:

	// ���� ������Ʈ�� ����κ��Դϴ�.
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
	//���⼭ �߰��ؼ� �����ϴ°�
	static std::vector<LightObject*> g_LightVec;
};

