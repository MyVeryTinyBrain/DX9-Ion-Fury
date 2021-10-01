#pragma once

#include "Component.h"

class Light : public Component
{
protected:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(BeginRender);

	OverrideComponentFunction(EndRender);

	OverrideComponentFunction(OnSleep);

public:

	void SetColor(const Color& color);

	Color GetColor() const;

	__declspec(property(get = GetColor, put = SetColor)) Color color;

public:

	static Color GetAmbientLight();

	static void SetAmbientLight(const Color& color);

protected:

	virtual void InitializeLightType(D3DLIGHTTYPE& lightType) = 0;

	virtual void UpdateLight(D3DLIGHT9& light) = 0;

private:

	unsigned int GetDisabledLightIndex() const;

	void EnableLight(unsigned int lightIndex);

	void DisableLight(unsigned int lightIndex);

protected:

	enum { LIGHT_MAX = 256 };

	static bool g_lightEnables[LIGHT_MAX];

	D3DLIGHT9 m_light = {};

	bool m_isEnabled = false;

	unsigned int m_lightIndex = 0;
};

