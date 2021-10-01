#pragma once

#include "Light.h"

class PointLight : public Light
{
	OverrideComponentFunction(Awake);

	virtual void InitializeLightType(D3DLIGHTTYPE& lightType) override;

	virtual void UpdateLight(D3DLIGHT9& light) override;

public:

	void SetRange(float range);

	float GetRange() const;

	__declspec(property(get = GetRange, put = SetRange)) float range;
};

