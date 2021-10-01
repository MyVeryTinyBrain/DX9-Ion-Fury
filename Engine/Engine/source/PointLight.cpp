#include "EngineBase.h"
#include "PointLight.h"
#include "Transform.h"

void PointLight::Awake()
{
	Light::Awake();

	m_light.Range = 10.0f;
}

void PointLight::InitializeLightType(D3DLIGHTTYPE& lightType)
{
	lightType = D3DLIGHT_POINT;
}

void PointLight::UpdateLight(D3DLIGHT9& light)
{
	light.Attenuation0 = 0.90f;
	light.Attenuation1 = 0.05f;
	light.Attenuation2 = 0.05f;

	light.Position = transform->position;
}

void PointLight::SetRange(float range)
{
	m_light.Range = range;
}

float PointLight::GetRange() const
{
	return m_light.Range;
}
