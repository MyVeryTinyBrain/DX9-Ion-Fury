#pragma once
class LightLoad : public Component
{
	DeclareStaticComponent(LightLoad);
public:
	OverrideComponentFunction(Awake);


public:
	HRESULT LightObjectLoad(const wstring& wstrFilePath);

};

