#pragma once
class LightLoad : public Component
{
	DeclareStaticComponent(LightLoad);


public:
	HRESULT LightObjectLoad(const wstring& wstrFilePath);

};

