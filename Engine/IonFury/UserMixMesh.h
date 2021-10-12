#pragma once

class UserMixMesh abstract : public Component
{
public:

	void SetMaterials(const Ref<Material>& material);

protected:

	std::vector<UserMeshRenderer*> m_renderers;
};

