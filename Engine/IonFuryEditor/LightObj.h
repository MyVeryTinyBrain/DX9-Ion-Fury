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

	void AddLightObject();


public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:
	LIGHT m_LightType;		// enum 
	
	GameObject* m_LightChildObject; //addcomponet �� Ÿ���� �־��ָ�ȴ�. 

	UserMeshRenderer* m_LightRenderer;

public:
	static std::vector<LightObj*> g_vecLight;


};

