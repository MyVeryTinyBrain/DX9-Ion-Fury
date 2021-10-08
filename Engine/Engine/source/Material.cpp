#include "EngineBase.h"
#include "Material.h"
#include "GraphicDevice.h"
#include "ResourceManager.h"

MaterialParameters Material::g_beforeParams;

void Material::Apply(bool ignoreCmp)
{
	auto device = GraphicDevice::GetInstance()->GetDevice();

	if (ignoreCmp || g_beforeParams.wireFrame != params.wireFrame)
	device->SetRenderState(D3DRS_FILLMODE, params.wireFrame ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	if (ignoreCmp || g_beforeParams.cullMode != params.cullMode)
	device->SetRenderState(D3DRS_CULLMODE, DWORD(params.cullMode));

	if (ignoreCmp || g_beforeParams.zWrite != params.zWrite)
	device->SetRenderState(D3DRS_ZWRITEENABLE, DWORD(params.zWrite));

	if (ignoreCmp || g_beforeParams.zRead != params.zRead)
	device->SetRenderState(D3DRS_ZENABLE, DWORD(params.zRead));

	if (ignoreCmp || g_beforeParams.zReadMode != params.zReadMode)
	device->SetRenderState(D3DRS_ZFUNC, DWORD(params.zReadMode));

	if (ignoreCmp || g_beforeParams.alphaTest != params.alphaTest)
	device->SetRenderState(D3DRS_ALPHATESTENABLE, DWORD(params.alphaTest));

	if (ignoreCmp || g_beforeParams.alphaRef != params.alphaRef)
	device->SetRenderState(D3DRS_ALPHAREF, DWORD(params.alphaRef));

	if (ignoreCmp || g_beforeParams.alpahTestMode != params.alpahTestMode)
	device->SetRenderState(D3DRS_ALPHAFUNC, DWORD(params.alpahTestMode));

	if (ignoreCmp || g_beforeParams.alphaBlend != params.alphaBlend)
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, DWORD(params.alphaBlend));

	if (ignoreCmp || g_beforeParams.blendOperation != params.blendOperation)
	device->SetRenderState(D3DRS_BLENDOP, DWORD(params.blendOperation));

	if (ignoreCmp || g_beforeParams.srcBlendFactor != params.srcBlendFactor)
	device->SetRenderState(D3DRS_SRCBLEND, DWORD(params.srcBlendFactor));

	if (ignoreCmp || g_beforeParams.dstBlendFactor != params.dstBlendFactor)
	device->SetRenderState(D3DRS_DESTBLEND, DWORD(params.dstBlendFactor));




	if (ignoreCmp || g_beforeParams.useLight != params.useLight)
	device->SetRenderState(D3DRS_LIGHTING, DWORD(params.useLight));

	if (ignoreCmp || g_beforeParams.useSpecular != params.useSpecular)
	device->SetRenderState(D3DRS_SPECULARENABLE, DWORD(params.useSpecular));

	if (ignoreCmp ||
		g_beforeParams.ambient != params.ambient ||
		g_beforeParams.diffuse != params.diffuse ||
		g_beforeParams.emissive != params.emissive ||
		g_beforeParams.specular != params.specular ||
		g_beforeParams.power != params.power)
	{
		D3DMATERIAL9 mat;
		mat.Ambient = params.ambient;
		mat.Diffuse = params.diffuse;
		mat.Emissive = params.emissive;
		mat.Specular = params.specular;
		mat.Power = params.power;
		device->SetMaterial(&mat);
	}

	g_beforeParams = params;
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
