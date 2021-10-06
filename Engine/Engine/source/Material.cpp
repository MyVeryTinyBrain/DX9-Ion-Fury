#include "EngineBase.h"
#include "Material.h"
#include "GraphicDevice.h"
#include "ResourceManager.h"

void Material::Apply()
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	device->SetRenderState(D3DRS_FILLMODE, params.wireFrame ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	device->SetRenderState(D3DRS_CULLMODE, DWORD(params.cullMode));

	device->SetRenderState(D3DRS_ZWRITEENABLE, DWORD(params.zWrite));

	device->SetRenderState(D3DRS_ZENABLE, DWORD(params.zRead));

	device->SetRenderState(D3DRS_ZFUNC, DWORD(params.zReadMode));

	device->SetRenderState(D3DRS_ALPHATESTENABLE, DWORD(params.alphaTest));

	device->SetRenderState(D3DRS_ALPHAREF, DWORD(params.alphaRef));

	device->SetRenderState(D3DRS_ALPHAFUNC, DWORD(params.alpahTestMode));

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, DWORD(params.alphaBlend));

	device->SetRenderState(D3DRS_BLENDOP, DWORD(params.blendOperation));

	device->SetRenderState(D3DRS_SRCBLEND, DWORD(params.srcBlendFactor));

	device->SetRenderState(D3DRS_DESTBLEND, DWORD(params.dstBlendFactor));




	device->SetRenderState(D3DRS_LIGHTING, DWORD(params.useLight));

	device->SetRenderState(D3DRS_SPECULARENABLE, DWORD(params.useSpecular));

	D3DMATERIAL9 mat;
	mat.Ambient = params.ambient;
	mat.Diffuse = params.diffuse;
	mat.Emissive = params.emissive;
	mat.Specular = params.specular;
	mat.Power = params.power;
	device->SetMaterial(&mat);
}

Material::Material(MaterialParameters& params) : ResourceObject()
{
	this->params = params;
}

Material::Material(MaterialParameters& params, wstring localPath, bool isShared) : ResourceObject(localPath, isShared)
{
	this->params = params;
}

Material::~Material()
{
}

Material* Material::Create(MaterialParameters& params, const wstring& localPath, bool isShared)
{
	Material* material = new Material(params, localPath, isShared);
	ResourceManager::GetInstance()->AddResource(material);
	return material;
}

Material* Material::CreateUnmanaged(MaterialParameters& params)
{
	Material* material = new Material(params);
	return material;
}

IClonable* Material::Clone()
{
	Material* material = new Material(this->params);
	return material;
}
