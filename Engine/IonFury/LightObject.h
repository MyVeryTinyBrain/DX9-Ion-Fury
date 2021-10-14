#pragma once

class LightObject :   public Component
{
	DeclareStaticComponent(LightObject);

	OverrideComponentFunction(Awake);


public:
	HRESULT LoadLightObject(const wstring& wstrFilePath);

public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:

	GameObject* m_LightChildObject; //addcomponet �� Ÿ���� �־��ָ�ȴ�. 

	UserMeshRenderer* m_LightRenderer;

public:
	static std::vector<LightObject*> g_vecLight;
};

