#pragma once

class LightObject :  public Light
{
public:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);


public:
	void LightSettings(const wstring& localPathMesh = L"../Resource/CubeUserMesh.mesh");



public:
	UserMeshRenderer* GetRenderer() { return m_LightRenderer; }

private:
	GameObject* m_LightChildObject;

	Light* m_LightType;

	UserMeshRenderer* m_LightRenderer;

public:
	Ref<Transform> m_Light;

};

