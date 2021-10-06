#include "EngineBase.h"
#include "Material.h"
#include "GraphicDevice.h"

void Material::Apply()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	device->SetRenderState(D3DRS_CULLMODE, DWORD(params.m_cullMode));

	device->SetRenderState(D3DRS_ZWRITEENABLE, DWORD(params.m_zWrite));

	device->SetRenderState(D3DRS_ZENABLE, DWORD(params.m_zRead));

	device->SetRenderState(D3DRS_ZFUNC, DWORD(params.m_zReadMode));

	device->SetRenderState(D3DRS_ALPHATESTENABLE, DWORD(params.m_alphaTest));

	device->SetRenderState(D3DRS_ALPHAREF, DWORD(params.m_alphaRef));

	device->SetRenderState(D3DRS_ALPHAFUNC, DWORD(params.m_alpahTestMode));

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, DWORD(params.m_alphaBlend));

	device->SetRenderState(D3DRS_BLENDOP, DWORD(params.m_blendOperation));

	device->SetRenderState(D3DRS_SRCBLEND, DWORD(params.m_srcBlendFactor));

	device->SetRenderState(D3DRS_DESTBLEND, DWORD(params.m_dstBlendFactor));

	device->SetRenderState(D3DRS_LIGHTING, DWORD(params.m_light));

	device->SetRenderState(D3DRS_SPECULARENABLE, DWORD(params.m_specular));

	D3DMATERIAL9 mat;
	mat.Ambient = params.m_ambient;
	mat.Diffuse = params.m_diffuse;
	mat.Emissive = params.m_emissive;
	mat.Specular = params.m_specular;
	mat.Power = params.m_power;
	device->SetMaterial(&mat);
}
