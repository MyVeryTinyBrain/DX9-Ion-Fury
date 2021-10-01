#include "EngineBase.h"
#include "DirectionalLight.h"
#include "Transform.h"

void DirectionalLight::Awake()
{
	Light::Awake();
}

void DirectionalLight::InitializeLightType(D3DLIGHTTYPE& lightType)
{
	lightType = D3DLIGHT_DIRECTIONAL;
}

void DirectionalLight::UpdateLight(D3DLIGHT9& light)
{
	light.Direction = -transform->up;
}
