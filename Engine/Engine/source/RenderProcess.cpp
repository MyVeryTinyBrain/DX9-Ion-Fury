#include "EngineBase.h"
#include "RenderProcess.h"
#include "Renderer.h"
#include "Material.h"

void RenderProcess::AddRenderTarget(Renderer* renderer)
{
	const Ref<Material>& material = renderer->material;

	if (material.IsNull())
		return;

	m_renderTargets[unsigned int(material->params.m_renderQueue)].push_back(renderer);
}
