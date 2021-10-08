#pragma once

#include "Component.h"

class Texture;
class Material;

class Renderer abstract : public Component
{
protected:

	enum { TEX_MAX = 8 };

protected:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(BeginRender);

public:

	virtual void Render() = 0;

public:

	uint8_t GetRenderLayerIndex() const;

	void SetRenderLayerIndex(uint8_t value);

	Ref<Texture> GetTexture(unsigned int index) const;

	void SetTexture(unsigned int index, const Ref<Texture>& texture);

	const Ref<Material>& GetMaterial() const;

	void SetMaterial(const Ref<Material>& material);

	int GetOverlayRenderOrder() const;

	void SetOverlayRenderOrder(int value);

	__declspec(property(get = GetRenderLayerIndex, put = SetRenderLayerIndex)) uint8_t renderLayerIndex;

	__declspec(property(get = GetMaterial, put = SetMaterial)) const Ref<Material>& material;

	__declspec(property(get = GetOverlayRenderOrder, put = SetOverlayRenderOrder)) int overlayRenderOrder;

protected:

	// ī�޶󿡼� �� ���̾ ������ �� �������� �׸��� ������ ���ϰ� �˴ϴ�.
	// 0 ~ 31 ������ ���� �����ϴ�.
	// 31�� �ʰ��ϴ� ���� �����ϸ� ��Ʈ ���꿡 ���ؼ� �׸��� �ʰ� �˴ϴ�.
	uint8_t m_renderLayerIndex = 0;

	Ref<Texture> m_textures[TEX_MAX];

	Ref<Material> m_material;

	// �������� ���� ť �����϶��� �׸��� �����Դϴ�.
	int m_overlayRenderOrder = 0;
};

