#pragma once

#include "Texture.h"

class RenderTexture : public Texture
{
	friend class ResourceManager;

protected:

	// Constructor for unmanaged resource
	RenderTexture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc);

	// Construct for managed resource
	RenderTexture(IDirect3DTexture9* texture, const D3DSURFACE_DESC& srcDesc, wstring localPath, bool isShared);

	virtual ~RenderTexture();

public:

	static RenderTexture* CreateRenderTexture(const UINT& width, const UINT& height, const D3DXCOLOR& color, const wstring& localPath, bool isShared = false);

	static RenderTexture* CreateUnmanagedRenderTexture(const UINT& width, const UINT& height, const D3DXCOLOR& color);

	static Texture* CreateFromFile(const wstring& localPath, bool isShared = true) = delete;

	static Texture* CreateInDirectX(const UINT& width, const UINT& height, const D3DXCOLOR& color, const wstring& localPath, bool isShared = false) = delete;

	static Texture* CreateUnmanagedInDirectX(const UINT& width, const UINT& height, const D3DXCOLOR& color) = delete;
	
};

