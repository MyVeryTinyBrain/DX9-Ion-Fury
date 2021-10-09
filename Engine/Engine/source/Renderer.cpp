#include "EngineBase.h"
#include "Renderer.h"
#include "GraphicDevice.h"
#include "Texture.h"
#include "RenderProcess.h"
#include "Resource.h"
#include "BuiltInResources.h"
#include "Material.h"

void Renderer::Awake()
{
	memset(m_textures, 0, sizeof(m_textures));

	m_material = Resource::FindAs<Material>(BuiltInGeometryMaterial);
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
		{
			device->SetTexture(i, 0);
			continue;
		}

		device->SetTexture(i, m_textures[i]->texture);
	}
}

uint8_t Renderer::GetRenderLayerIndex() const
{
	return m_renderLayerIndex;
}

void Renderer::SetRenderLayerIndex(uint8_t value)
{
	m_renderLayerIndex = value;
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

int Renderer::GetOverlayRenderOrder() const
{
	return m_overlayRenderOrder;
}

void Renderer::SetOverlayRenderOrder(int value)
{
	m_overlayRenderOrder = value;
}
