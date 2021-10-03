#include "EngineBase.h"
#include "SpotLight.h"
#include "Transform.h"

void SpotLight::Awake()
{
	Light::Awake();

	m_light.Range = 30.0f;

	SetOutsideAngle(90);

	SetInsideAngleRatio(0.5f);
}

void SpotLight::InitializeLightType(D3DLIGHTTYPE& lightType)
{
	lightType = D3DLIGHT_SPOT;
}

void SpotLight::UpdateLight(D3DLIGHT9& light)
{
	light.Attenuation0 = 0.90f;
	light.Attenuation1 = 0.05f;
	light.Attenuation2 = 0.05f;
	light.Falloff = 1.0f;

	light.Position = transform->position;

	light.Direction = transform->forward;
}

void SpotLight::SetRange(float range)
{
	m_light.Range = range;
}

float SpotLight::GetRange() const
{
	return m_light.Range;
}

void SpotLight::SetOutsideAngle(float angle)
{
	m_light.Phi = angle * Deg2Rad;
}

float SpotLight::GetOutsideAngle() const
{
	return m_light.Phi * Rad2Deg;
}

void SpotLight::SetInsideAngleRatio(float ratio)
{
	if (ratio <= 0)
		ratio = 0.0001f;

	m_light.Theta = ratio * m_light.Phi;
}

float SpotLight::GetInsideAngleRatio() const
{
	return m_light.Theta / m_light.Phi;
}
