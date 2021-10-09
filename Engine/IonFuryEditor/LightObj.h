#pragma once


enum class LIGHT {AMBINENT, DIRECTIONAL, POINT, SPOT, END};

class LightObj :  public Component
{
public:

	// ���� ������Ʈ�� ����κ��Դϴ�.
	DeclareStaticComponent(LightObj);

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

public:
	void LightSettings(const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh");

	void SetLightType(const wstring& lightType);

	static LightObj* LightPick();

	CString& GetName() { return m_strType; }


public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:
	LIGHT m_LightType = LIGHT::END;		// enum 
	
	GameObject* m_LightChildObject; //addcomponet �� Ÿ���� �־��ָ�ȴ�. 

	UserMeshRenderer* m_LightRenderer;

	CString m_strType;

public:
	static std::vector<LightObj*> g_vecLight;


};

