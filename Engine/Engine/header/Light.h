#pragma once

#include "Component.h"

class Light : public Component
{
protected:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

public:

	void SetColor(const Color& color);

	Color GetColor() const;

	float GetAmbientFactor() const;

	void SetAmbientFactor(float factor);

	__declspec(property(get = GetColor, put = SetColor)) Color color;

	__declspec(property(get = GetAmbientFactor, put = SetAmbientFactor)) float ambientFactor;

public:

	static Color GetGlobalAmbientLight();

	static void SetGlobalAmbientLight(const Color& color);

public:

	static void BeginLight();

	static void EndLight();

private:

	void ActiveLight();

	void DeactiveLight();

protected:

	virtual void InitializeLightType(D3DLIGHTTYPE& lightType) = 0;

	virtual void UpdateLight(D3DLIGHT9& light) = 0;

private:

	unsigned int GetDisabledLightIndex() const;

	void EnableLight(unsigned int lightIndex);

	void DisableLight(unsigned int lightIndex);

protected:

	enum { LIGHT_MAX = 10 };

	static bool g_lightEnables[LIGHT_MAX];

	static std::vector<Light*> g_lights;

	D3DLIGHT9 m_light = {};

	bool m_isEnabled = false;

	unsigned int m_lightIndex = 0;

	float m_ambientFactor = 0.0f;
};

