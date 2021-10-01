#pragma once

class GraphicDevice
{
	DeclareSingletone(GraphicDevice);

	GraphicDevice();

	~GraphicDevice();

public:

	HRESULT InitializeWithShowWindow(HINSTANCE hInst, int width, int height, bool windowed, LPCWSTR title, WNDPROC wndProc);

	HRESULT Initialize(HWND hWnd, UINT width, UINT height, BOOL windowed);

	void Release();

	HRESULT Reset(HWND hWnd, UINT width, UINT height, BOOL windowed);

	HRESULT BeginRender();

	HRESULT EndRender(HWND hWnd = nullptr);

	HWND GetWindowHandle() const;

	Vec2 GetSize() const;

	float GetAspect() const;

	IDirect3DDevice9* GetDevice() const;

	const Color& GetBackgroundColor() const;

	void SetBackgroundColor(const Color& color);

	ID3DXLine* GetLine() const;

private:

	HRESULT CreateDirect3DPresendParamaters(HWND hWnd, UINT width, UINT height, D3DPRESENT_PARAMETERS* pD3DPP) const;

	HRESULT CreateDirect3D(IDirect3D9** ppD3D) const;

	HRESULT CreateDevice(IDirect3D9* pD3D, HWND hWnd, UINT width, UINT height, BOOL windowed, IDirect3DDevice9** ppDevice) const;

	HRESULT SetupComponents();

	HRESULT ReleaseComponents();

private:

	IDirect3D9* m_d3d = nullptr;

	IDirect3DDevice9* m_device = nullptr;

	Color m_bgColor = Color::blue();

	ID3DXLine* m_line = nullptr;
};

