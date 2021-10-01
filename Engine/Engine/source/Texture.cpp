#include "EngineBase.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "GraphicDevice.h"

Texture::Texture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc)
	: ResourceObject()
{
	m_texture = texture;
	m_srcDesc = srcDesc;
}

Texture::Texture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc, wstring localPath, bool isShared)
	: ResourceObject(localPath, isShared)
{
	m_texture = texture;
	m_srcDesc = srcDesc;
}

Texture::~Texture()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

Texture* Texture::CreateFromFile(const wstring& localPath, bool isShared)
{
	if (ResourceManager::GetInstance()->Exist(localPath))
	{
		return nullptr;
	}

	HRESULT res;
	IDirect3DTexture9* texture;
	D3DSURFACE_DESC desc;

	res = D3DXCreateTextureFromFile(GraphicDevice::GetInstance()->GetDevice(), localPath.c_str(), &texture);
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

	Texture* resource = new Texture(texture, desc, localPath, isShared);

	ResourceManager::GetInstance()->AddResource(resource);

	return resource;
}

Texture* Texture::CreateInDirectX(const UINT& width, const UINT& height, const D3DXCOLOR& color, const wstring& localPath, bool isShared)
{
	if (ResourceManager::GetInstance()->Exist(localPath))
	{
		return nullptr;
	}

	HRESULT res;
	IDirect3DTexture9* texture;
	D3DSURFACE_DESC desc;

	res = D3DXCreateTexture(GraphicDevice::GetInstance()->GetDevice(), width, height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture);
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
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			size_t i = y * width + x;
			colors[i] = color;
		}
	}
	texture->UnlockRect(0);

	Texture* resource = new Texture(texture, desc, localPath, isShared);

	ResourceManager::GetInstance()->AddResource(resource);

	return resource;
}

IDirect3DTexture9* Texture::GetTexture() const
{
	return m_texture;
}

const D3DSURFACE_DESC& Texture::GetSourceDesc() const
{
	return m_srcDesc;
}

Vec2 Texture::GetSize() const
{
	return Vec2(float(m_srcDesc.Width), float(m_srcDesc.Height));
}

IClonable* Texture::Clone()
{
	if (!m_texture)
		return nullptr;

	HRESULT res;
	IDirect3DTexture9* destTexture;

	res = D3DXCreateTexture(GraphicDevice::GetInstance()->GetDevice(), m_srcDesc.Width, m_srcDesc.Height, 0, m_srcDesc.Usage, m_srcDesc.Format, m_srcDesc.Pool, &destTexture);
	if (FAILED(res))
	{
		return nullptr;
	}

	D3DLOCKED_RECT destPixels, srcPixels;
	destTexture->LockRect(0, &destPixels, 0, D3DLOCK_DISCARD);
	m_texture->LockRect(0, &srcPixels, 0, D3DLOCK_DISCARD);
	memcpy(destPixels.pBits, srcPixels.pBits, sizeof(DWORD) * m_srcDesc.Width * m_srcDesc.Height);
	destTexture->UnlockRect(0);
	m_texture->UnlockRect(0);

	Texture* resource = new Texture(texture, m_srcDesc);
	
	return resource;
}

Texture::operator IDirect3DTexture9* () const
{
	return m_texture;
}
