#include "shared_stdafx.h"
#include "Number.h"
#include "OverlayRenderOrders.h"
#include "RenderLayers.h"

void Number::Awake()
{
	for (int i = 0; i < 10; ++i)
	{
		wchar_t buffer[256];
		swprintf_s(buffer, L"../SharedResource/Texture/numfont/%d.png", i);

		m_nums[i] = Resource::FindAs<Texture>(buffer);
	}

	m_renderer = gameObject->AddComponent<UserMeshRenderer>();
	m_renderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
	m_renderer->overlayRenderOrder = (int)OverlayRenderOrders::UIFont;
	m_renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
	m_renderer->renderLayerIndex = uint8_t(RenderLayers::Overlay);

	number = 0;
}

void Number::SetNumber(unsigned int digit)
{
	m_numIndex = digit;
	m_renderer->SetTexture(0, m_nums[m_numIndex]);
}

unsigned int Number::GetNumber() const
{
	return m_numIndex;
}
