﻿#include "stdafx.h"
#include "Main.h"
#include "TestScene.h"

HINSTANCE hInst;
EngineWorld world;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	world.InitializeWithShowWindow(hInstance, 1280, 720, true, L"Ion Fury", WndProc);

	SceneManager::ChangeScene(new TestScene);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		world.Step();
	}

	world.Release();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	world.WindowProcedure(message, wParam, lParam);

	switch (message)
	{
		case WM_KEYDOWN:
			{
				if (wParam == VK_ESCAPE)
					DestroyWindow(hWnd);
			}
			break;
		case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}