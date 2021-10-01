#pragma once

#define ENGINE_EXPORT

#define ENGINE_STATIC_LIB

#ifndef ENGINE_STATIC_LIB 
#ifdef ENGINE_EXPORT
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#include "LibraryLink.h"

#include <cassert>

#include <iostream>

#include <string>

using std::string;

using std::wstring;

using std::cout;

using std::endl;

using std::wcout;

#include <thread>

#include <mutex>

#include <d3d9.h>

#include <d3dx9.h>

#include <PxPhysics.h>

#include <PxPhysicsAPI.h>

using namespace physx;

#include "PhysicsBase.h"

#include <Windows.h>

#include "D3DXMathEx.h"

using namespace MathEx;

#include "DataStructEx.h"

#include "Templates.h"

#include "Types.h"

#include "Defines.h"

#pragma region debugmemoryblock
#include <crtdbg.h>
#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define BeginDebugMemoryBlock _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define BeginDebugMemoryBlock
#endif
#pragma endregion

#pragma region console
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#pragma endregion
