#include "EngineBase.h"
#include "Light.h"
#include "GraphicDevice.h"

bool Light::g_lightEnables[LIGHT_MAX] = {};

void Light::Awake()
{
	ZeroMemory(&m_light, sizeof(m_light));

	SetColor(Color::white());

	InitializeLightType(m_light.Type);

	SetColor(m_light.Diffuse);
}

void Light::BeginRender()
{
	unsigned int lightIndex = GetDisabledLightIndex();
	if (lightIndex < LIGHT_MAX)
		EnableLight(lightIndex);
}

void Light::EndRender()
{
	if (m_isEnabled)
		DisableLight(m_lightIndex);
}

void Light::OnSleep()
{
	if (m_isEnabled)
		DisableLight(m_lightIndex);
}

void Light::SetColor(const Color& color)
{
	float ambientFactor = 1.0f;
	//if (m_light.Type == D3DLIGHT_SPOT)
	//	ambientFactor = 0.0f;

	m_light.Ambient = color * 0.6f * ambientFactor;
	m_light.Diffuse = color;
	m_light.Specular = color * 0.6f;
}

Color Light::GetColor() const
{
	return m_light.Diffuse;
}

Color Light::GetAmbientLight()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	Color ambientColor;
	device->GetRenderState(D3DRS_AMBIENT, (DWORD*)&ambientColor);
	return ambientColor;
}

void Light::SetAmbientLight(const Color& color)
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	device->SetRenderState(D3DRS_AMBIENT, color);
}

unsigned int Light::GetDisabledLightIndex() const
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	for (unsigned int i = 0; i < LIGHT_MAX; ++i)
	{
		if (!g_lightEnables[i])
			return i;
	}

	return LIGHT_MAX;
}

void Light::EnableLight(unsigned int lightIndex)
{
	if (lightIndex > LIGHT_MAX)
		return;

	if (m_isEnabled)
		return;

	auto device = GraphicDevice::GetInstance()->GetDevice();

	UpdateLight(m_light);

	m_lightIndex = lightIndex;

	m_isEnabled = true;

	g_lightEnables[m_lightIndex] = true;

	device->SetLight(m_lightIndex, &m_light);

	device->LightEnable(m_lightIndex, TRUE);
}

void Light::DisableLight(unsigned int lightIndex)
{
	if (lightIndex != m_lightIndex)
		return;

	if (lightIndex > LIGHT_MAX)
		return;

	if (!m_isEnabled)
		return;

	auto device = GraphicDevice::GetInstance()->GetDevice();

	m_lightIndex = lightIndex;

	m_isEnabled = false;

	g_lightEnables[m_lightIndex] = false;

	device->LightEnable(m_lightIndex, FALSE);
}
