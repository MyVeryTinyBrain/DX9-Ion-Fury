#include "EngineBase.h"
#include "GraphicDevice.h"

#define D3DRelease(x)		if(x)	{ x->Release(); x = NULL;	}

#define IF_FAILED_RETURN(hResult)													\
if(FAILED(hResult))																	\
{																					\
	return hResult;																	\
}

ImplementSingletone(GraphicDevice);

GraphicDevice::GraphicDevice()
{
}

GraphicDevice::~GraphicDevice()
{
	Release();
}

HRESULT GraphicDevice::InitializeWithShowWindow(HINSTANCE hInst, int width, int height, bool windowed, LPCWSTR title, WNDPROC wndProc)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = FALSE;
	wc.lpszClassName = title;

	if (!RegisterClass(&wc))
		return E_FAIL;

	RECT size = { 0,0,width,height };
	AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindow(
		title, title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		size.right - size.left, size.bottom - size.top,
		NULL, NULL,
		hInst,
		NULL);

	if (!hWnd)
		return E_FAIL;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return Initialize(hWnd, width, height, windowed);
}

HRESULT GraphicDevice::Initialize(HWND hWnd, UINT width, UINT height, BOOL windowed)
{
	HRESULT res;

	res = CreateDirect3D(&m_d3d);
	IF_FAILED_RETURN(res);

	res = CreateDevice(m_d3d, hWnd, width, height, windowed, &m_device);
	IF_FAILED_RETURN(res);

	res = SetupComponents();
	IF_FAILED_RETURN(res);

	return S_OK;
}

void GraphicDevice::Release()
{
	ReleaseComponents();

	D3DRelease(m_device);
	D3DRelease(m_d3d);
}

HRESULT GraphicDevice::Reset(HWND hWnd, UINT width, UINT height, BOOL windowed)
{
	HRESULT res;

	D3DPRESENT_PARAMETERS d3dpp;
	CreateDirect3DPresendParamaters(hWnd, width, height, &d3dpp);
	d3dpp.Windowed = windowed;

	res = m_device->Reset(&d3dpp);
	IF_FAILED_RETURN(res);

	return S_OK;
}

HRESULT GraphicDevice::BeginRender()
{
	HRESULT res;

	res = m_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, m_bgColor, 1.0f, 0);
	IF_FAILED_RETURN(res);

	res = m_device->BeginScene();
	IF_FAILED_RETURN(res);

	return S_OK;
}

HRESULT GraphicDevice::EndRender(HWND hWnd)
{
	HRESULT res;

	res = m_device->EndScene();
	IF_FAILED_RETURN(res);

	res = m_device->Present(0, 0, hWnd, 0);
	IF_FAILED_RETURN(res);

	return S_OK;
}

HWND GraphicDevice::GetWindowHandle() const
{
	HRESULT res;

	D3DDEVICE_CREATION_PARAMETERS cp;
	res = m_device->GetCreationParameters(&cp);

	if (FAILED(res))
		return NULL;
	return cp.hFocusWindow;
}

Vec2 GraphicDevice::GetSize() const
{
	RECT rect;

	GetClientRect(GetWindowHandle(), &rect);

	return Vec2(float(rect.right - rect.left), float(rect.bottom - rect.top));
}

float GraphicDevice::GetAspect() const
{
	Vec2 size = GetSize();

	return size.x / size.y;
}

IDirect3DDevice9* GraphicDevice::GetDevice() const
{
	return m_device;
}

const Color& GraphicDevice::GetBackgroundColor() const
{
	return m_bgColor;
}

void GraphicDevice::SetBackgroundColor(const Color& color)
{
	m_bgColor = color;
}

ID3DXLine* GraphicDevice::GetLine() const
{
	return m_line;
}

HRESULT GraphicDevice::CreateDirect3DPresendParamaters(HWND hWnd, UINT width, UINT height, D3DPRESENT_PARAMETERS* pD3DPP) const
{
	D3DPRESENT_PARAMETERS pp{};
	pp.BackBufferWidth = width;
	pp.BackBufferHeight = height;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE;	// 샘플링을 하지 않습니다.
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;			// 백버퍼 주소 교체 방식을 사용합니다.
	pp.hDeviceWindow = hWnd;
	pp.Windowed = true;												// 창 모드 설정입니다.
	pp.EnableAutoDepthStencil = true;								// 깊이 버퍼와 스텐실을 사용합니다.
	pp.AutoDepthStencilFormat = D3DFORMAT::D3DFMT_D24S8;
	pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// 전체화면에서의 새로고침 빈도를 설정합니다.
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;		// 백버퍼 교환을 즉시 하도록 합니다
	*pD3DPP = pp;
	return S_OK;
}

HRESULT GraphicDevice::CreateDirect3D(IDirect3D9** ppD3D) const
{
	*ppD3D = Direct3DCreate9(D3D_SDK_VERSION);
	return S_OK;
}

HRESULT GraphicDevice::CreateDevice(IDirect3D9* pD3D, HWND hWnd, UINT width, UINT height, BOOL windowed, IDirect3DDevice9** ppDevice) const
{
	HRESULT res;

	D3DPRESENT_PARAMETERS d3dpp;
	CreateDirect3DPresendParamaters(hWnd, width, height, &d3dpp);
	d3dpp.Windowed = windowed;

	D3DCAPS9 caps;
	res = pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	IF_FAILED_RETURN(res);

	DWORD vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	res = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, ppDevice);
	IF_FAILED_RETURN(res);

	return S_OK;
}

HRESULT GraphicDevice::ReleaseComponents()
{
	D3DRelease(m_line);

	return E_NOTIMPL;
}

HRESULT GraphicDevice::SetupComponents()
{
	HRESULT res;

	ID3DXLine* line = nullptr;
	res = D3DXCreateLine(m_device, &m_line);
	IF_FAILED_RETURN(res);

	return S_OK;
}
