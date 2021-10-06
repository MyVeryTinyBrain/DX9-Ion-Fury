#include "EngineBase.h"
#include "RenderTexture.h"
#include "GraphicDevice.h"
#include "ResourceManager.h"

RenderTexture::RenderTexture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc) : 
    Texture(texture, srcDesc)
{
}

RenderTexture::RenderTexture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc, wstring localPath, bool isShared) :
    Texture(texture, srcDesc, localPath, isShared)
{
}

RenderTexture::~RenderTexture()
{
}

RenderTexture* RenderTexture::CreateRenderTexture(const UINT& width, const UINT& height, const D3DXCOLOR& color, const wstring& localPath, bool isShared)
{
	if (ResourceManager::GetInstance()->Exist(localPath))
	{
		return nullptr;
	}

	HRESULT res;
	IDirect3DTexture9* texture;
	D3DSURFACE_DESC desc;

	res = D3DXCreateTexture(GraphicDevice::GetInstance()->GetDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture);
	if (FAILED(res))
	{
		return nullptr;
	}

	res = texture->GetLevelDesc(0, &desc);
	if (FAILED(res))
	{
		texture->Release();
		return nullptr;
	}

	D3DLOCKED_RECT pixels;
	texture->LockRect(0, &pixels, 0, D3DLOCK_DISCARD);
	DWORD* colors = (DWORD*)pixels.pBits;
	if (colors)
	{
		for (size_t y = 0; y < height; ++y)
		{
			for (size_t x = 0; x < width; ++x)
			{
				size_t i = y * width + x;
				colors[i] = color;
			}
		}
	}
	texture->UnlockRect(0);

	RenderTexture* resource = new RenderTexture(texture, desc, localPath, isShared);

	ResourceManager::GetInstance()->AddResource(resource);

	return resource;
}

RenderTexture* RenderTexture::CreateUnmanagedRenderTexture(const UINT& width, const UINT& height, const D3DXCOLOR& color)
{
	HRESULT res;
	IDirect3DTexture9* texture;
	D3DSURFACE_DESC desc;

	res = D3DXCreateTexture(GraphicDevice::GetInstance()->GetDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture);
	if (FAILED(res))
	{
		return nullptr;
	}

	res = texture->GetLevelDesc(0, &desc);
	if (FAILED(res))
	{
		texture->Release();
		return nullptr;
	}

	D3DLOCKED_RECT pixels;
	texture->LockRect(0, &pixels, 0, D3DLOCK_DISCARD);
	DWORD* colors = (DWORD*)pixels.pBits;
	if (colors)
	{
		for (size_t y = 0; y < height; ++y)
		{
			for (size_t x = 0; x < width; ++x)
			{
				size_t i = y * width + x;
				colors[i] = color;
			}
		}
	}
	texture->UnlockRect(0);

	RenderTexture* resource = new RenderTexture(texture, desc);

	return resource;
}
