#pragma once

#include "Component.h"

class Texture;
class Material;

class Renderer : public Component
{
protected:

	enum { TEX_MAX = 8 };

protected:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(BeginRender);

	OverrideComponentFunction(Render);

public:

	Ref<Texture> GetTexture(unsigned int index) const;

	void SetTexture(unsigned int index, const Ref<Texture>& texture);

	const Ref<Material>& GetMaterial() const;

	void SetMaterial(const Ref<Material>& material);

	__declspec(property(get = GetMaterial, put = SetMaterial))  const Ref<Material>& material;

protected:

	Ref<Texture> m_textures[TEX_MAX];

	Ref<Material> m_material = nullptr;
};

