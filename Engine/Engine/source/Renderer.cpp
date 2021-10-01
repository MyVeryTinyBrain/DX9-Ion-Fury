#include "EngineBase.h"
#include "Renderer.h"
#include "GraphicDevice.h"
#include "Texture.h"

void Renderer::Awake()
{
	m_allowLighting = true;

	m_specular = false;

	memset(m_textures, 0, sizeof(m_textures));

	m_material.Ambient = Color::white();
	m_material.Diffuse = Color::white();
	m_material.Emissive = Color::black();
	m_material.Specular = Color::white();
	m_material.Power = 1.0f;
}

void Renderer::Render()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	device->SetRenderState(D3DRS_LIGHTING, m_allowLighting);

	device->SetRenderState(D3DRS_SPECULARENABLE, m_specular);

	for (unsigned int i = 0; i < TEX_MAX; ++i)
	{
		if (!m_textures[i])
			continue;

		device->SetTexture(i, m_textures[i]->texture);

		device->SetMaterial(&m_material);
	}
}

Ref<Texture> Renderer::GetTexture(unsigned int index) const
{
	if (index >= TEX_MAX)
		return Ref<Texture>();
	return m_textures[index];
}

void Renderer::SetTexture(unsigned int index, const Ref<Texture>& texture)
{
	if (index >= TEX_MAX)
		return;
	m_textures[index] = texture;
}

bool Renderer::IsAllowLighting() const
{
	return m_allowLighting;
}

void Renderer::SetAllowLighting(bool value)
{
	m_allowLighting = value;
}
