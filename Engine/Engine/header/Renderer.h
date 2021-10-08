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

	// 카메라에서 이 레이어를 참조해 이 렌더러를 그릴지 말지를 정하게 됩니다.
	// 0 ~ 31 까지의 값을 가집니다.
	// 31를 초과하는 값을 설정하면 비트 연산에 의해서 그리지 않게 됩니다.
	uint8_t m_renderLayerIndex = 0;

	Ref<Texture> m_textures[TEX_MAX];

	Ref<Material> m_material;

	// 오버레이 렌더 큐 설정일때의 그리기 순서입니다.
	int m_overlayRenderOrder = 0;
};

