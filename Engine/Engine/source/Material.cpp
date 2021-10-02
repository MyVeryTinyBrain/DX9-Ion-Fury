#include "EngineBase.h"
#include "Material.h"
#include "GraphicDevice.h"

void Material::ApplyRenderStates()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	device->SetRenderState(D3DRS_CULLMODE, DWORD(m_param.m_cullMode));

	device->SetRenderState(D3DRS_ZWRITEENABLE, DWORD(m_param.m_zWrite));

	device->SetRenderState(D3DRS_ZENABLE, DWORD(m_param.m_zRead));

	device->SetRenderState(D3DRS_ZFUNC, DWORD(m_param.m_zReadMode));

	device->SetRenderState(D3DRS_ALPHATESTENABLE, DWORD(m_param.m_alphaTest));

	device->SetRenderState(D3DRS_ALPHAREF, DWORD(m_param.m_alphaRef));

	device->SetRenderState(D3DRS_ALPHAFUNC, DWORD(m_param.m_alpahTestMode));

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, DWORD(m_param.m_alphaBlend));

	device->SetRenderState(D3DRS_BLENDOP, DWORD(m_param.m_blendOperation));

	device->SetRenderState(D3DRS_SRCBLEND, DWORD(m_param.m_srcBlendFactor));

	device->SetRenderState(D3DRS_DESTBLEND, DWORD(m_param.m_dstBlendFactor));

	device->SetRenderState(D3DRS_LIGHTING, DWORD(m_param.m_light));

	device->SetRenderState(D3DRS_SPECULARENABLE, DWORD(m_param.m_specular));
}

bool Material::IsAlphaBlend() const
{
	return m_param.m_alphaBlend;
}

void Material::SetAlphaBlend(bool value)
{
	m_param.m_alphaBlend = value;
}
