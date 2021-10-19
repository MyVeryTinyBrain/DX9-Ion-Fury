#pragma once

class UserMixMesh abstract : public Component
{
public:

	void SetMaterials(const Ref<Material>& material);

	void SetRenderLayers(int layerIndex);

protected:

	std::vector<UserMeshRenderer*> m_renderers;
};

