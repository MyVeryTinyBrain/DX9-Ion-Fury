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
	void LightSettings(const wstring& localPathMesh = BuiltInCubeUserMesh
		, const wstring& localPathTexture = L"../SharedResource/Texture/Dev.png");

	static LightObj* LightPick();

	CString& GetName() { return m_strName; }


public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:
	LIGHT m_LightType = LIGHT::END;		// enum 
	
	GameObject* m_LightChildObject; //addcomponet �� Ÿ���� �־��ָ�ȴ�. 

	UserMeshRenderer* m_LightRenderer;

	CString m_strName;
	CString m_strTag;


public:
	static std::vector<LightObj*> g_vecLight;


};

