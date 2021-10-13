#pragma once


enum class LIGHT { AMBINENT, DIRECTIONAL, POINT, SPOT, END };

class LightObj : public Component
{
public:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

public:

	static void LightPick(const CString& name);

	void RequireDestroy();

public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:
	LIGHT m_LightType = LIGHT::END;		// enum 

	GameObject* m_LightChildObject; //addcomponet �� Ÿ���� �־��ָ�ȴ�. 

	UserMeshRenderer* m_LightRenderer;




public:
	static std::vector<LightObj*> g_vecLight;

private:
	bool m_destroyRequire = false;
};

