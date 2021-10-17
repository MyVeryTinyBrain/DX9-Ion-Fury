#include "stdafx.h"
#include "UserMixMesh.h"

void UserMixMesh::SetMaterials(const Ref<Material>& material)
{
	for (auto& renderer : m_renderers)
	{
		renderer->material = material;
	}
}

void UserMixMesh::SetRenderLayers(int layerIndex)
{
	for (auto& renderer : m_renderers)
	{
		renderer->renderLayerIndex = layerIndex;
	}
}
