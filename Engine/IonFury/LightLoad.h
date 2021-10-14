#pragma once
class LightLoad : public Component
{
	DeclareStaticComponent(LightLoad);
public:
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

public:
	HRESULT LightObjectLoad(const wstring& wstrFilePath);

public:
	static std::vector<LightLoad*> g_vecLight;

};

