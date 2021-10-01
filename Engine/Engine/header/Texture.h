#pragma once

#include "ResourceObject.h"

class Texture : public ResourceObject, public IClonable
{
	friend class ResourceManager;

protected:

	// Constructor for unmanaged resource
	Texture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc);

	// Construct for managed resource
	Texture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc, wstring localPath, bool isShared);

	virtual ~Texture();

public:

	static Texture* CreateFromFile(const wstring& localPath, bool isShared = true);

	static Texture* CreateInDirectX(const UINT& width, const UINT& height, const D3DXCOLOR& color, const wstring& localPath, bool isShared = false);

	IDirect3DTexture9* GetTexture() const;

	const D3DSURFACE_DESC& GetSourceDesc() const;

	Vec2 GetSize() const;

	virtual IClonable* Clone() override;

	operator IDirect3DTexture9* () const;

	__declspec(property(get = GetTexture)) IDirect3DTexture9* texture;

	__declspec(property(get = GetSourceInfo)) const D3DXIMAGE_INFO& srcInfo;

	__declspec(property(get = GetSize)) Vec2 size;

private:

	IDirect3DTexture9* m_texture;

	D3DSURFACE_DESC m_srcDesc;
};

