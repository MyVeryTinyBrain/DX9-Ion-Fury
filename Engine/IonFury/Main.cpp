#include "stdafx.h"
#include "Main.h"
#include "PhysicsInitialize.h"
#include <SoundMgr.h>
#include "TestScene.h"
#include "TestScene2.h"
#include "TestScene3.h"
#include "TestSceneSeob.h"

#include <AmmoBackup.h>
#include "Map0.h"
#include "Map1.h"

#ifndef _AFX

HINSTANCE hInst;
EngineWorld world;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	world.InitializeWithShowWindow(hInstance, 1280, 720, true, L"Ion Fury", WndProc);

	PhysicsInitialize::Initialize();

	SoundMgr::Get_Instance()->Initialize();

	AmmoBackup::GetInstance()->current->revolverLoadedAmmo = 120;
	AmmoBackup::GetInstance()->current->revolverTotalAmmo = 900;
	AmmoBackup::GetInstance()->Backup();


	SceneManager::ChangeScene(new Map0);

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

	SoundMgr::Destroy_Instance();

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

#endif
