#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
	OverrideComponentFunction(Awake);

	virtual void InitializeLightType(D3DLIGHTTYPE& lightType) override;

	virtual void UpdateLight(D3DLIGHT9& light) override;
};

