#include "EngineBase.h"
#include "Renderer.h"
#include "GraphicDevice.h"
#include "Texture.h"
#include "RenderProcess.h"

void Renderer::Awake()
{
	memset(m_textures, 0, sizeof(m_textures));
}

void Renderer::BeginRender()
{
	GraphicDevice::GetInstance()->GetRenderProcess()->AddRenderTarget(this);
}

void Renderer::Render()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	for (unsigned int i = 0; i < TEX_MAX; ++i)
	{
		if (!m_textures[i])
			continue;

		device->SetTexture(i, m_textures[i]->texture);
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

const Ref<Material>& Renderer::GetMaterial() const
{
	return m_material;
}

void Renderer::SetMaterial(const Ref<Material>& material)
{
	m_material = material;
}
