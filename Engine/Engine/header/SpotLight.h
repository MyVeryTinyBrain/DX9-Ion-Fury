#pragma once

#include "Light.h"

class SpotLight : public Light
{
	OverrideComponentFunction(Awake);

	virtual void InitializeLightType(D3DLIGHTTYPE& lightType) override;

	virtual void UpdateLight(D3DLIGHT9& light) override;

public:

	void SetRange(float range);

	float GetRange() const;

	void SetOutsideAngle(float angle);

	float GetOutsideAngle() const;

	void SetInsideAngleRatio(float ratio);

	float GetInsideAngleRatio() const;

	__declspec(property(get = GetRange, put = SetRange)) float range;

	__declspec(property(get = GetOutsideAngle, put = SetOutsideAngle)) float outsideAngle;

	__declspec(property(get = GetInsideAngleRatio, put = SetInsideAngleRatio)) float insideAngleRatio;
};

