#pragma once

class EngineWorld
{
public:

	HRESULT InitializeWithShowWindow(HINSTANCE hInst, int width, int height, bool windowed, LPCWSTR title, WNDPROC wndProc);

	HRESULT Initialize(HWND hWnd, UINT width, UINT height, BOOL windowed);

	HRESULT WindowProcedure(UINT message, WPARAM wParam, LPARAM lParam);

	HRESULT Step();

	HRESULT Release();

public:

	bool IsInitialized() const;

private:

	bool m_initialized = false;

	float m_fpsCheckElapsed = 0;

	unsigned int m_fpsCount = 0;
};

