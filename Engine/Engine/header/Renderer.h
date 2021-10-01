#pragma once

#include "Component.h"

class Texture;

class Renderer : public Component
{
protected:

	enum { TEX_MAX = 8 };

protected:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Render);

public:

	Ref<Texture> GetTexture(unsigned int index) const;

	void SetTexture(unsigned int index, const Ref<Texture>& texture);

	bool IsAllowLighting() const;

	void SetAllowLighting(bool value);

	__declspec(property(get = IsAllowLighting, put = SetAllowLighting)) bool allowLighting;

protected:

	bool m_allowLighting;

	bool m_specular;

	Ref<Texture> m_textures[TEX_MAX];

	D3DMATERIAL9 m_material;
};

