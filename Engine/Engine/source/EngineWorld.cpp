#include "EngineBase.h"
#include "EngineWorld.h"
#include "GraphicDevice.h"
#include "Input.h"
#include "CentralTimeElement.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "PhysicsDevice.h"
#include "BuiltIn.h"
#include "SharedResourceLoader.h"
#include "RenderProcess.h"

HRESULT EngineWorld::InitializeWithShowWindow(HINSTANCE hInst, int width, int height, bool windowed, LPCWSTR title, WNDPROC wndProc)
{
	BeginDebugMemoryBlock

	HRESULT res;

	res = GraphicDevice::GetInstance()->InitializeWithShowWindow(hInst, width, height, windowed, title, wndProc);
	if (FAILED(res))
	{
		GraphicDevice::GetInstance()->Release();
		return E_FAIL;
	}

	CentralTimeElement::GetInstance()->Initialize(144, 30);

	PhysicsDevice::GetInstance()->Initialize();

	BuiltIn::MakeBuiltInResources();

	SharedResourceLoader::LoadSharedResources();

	m_initialized = true;

	srand(unsigned int(time(NULL)));

	return S_OK;
}

HRESULT EngineWorld::Initialize(HWND hWnd, UINT width, UINT height, BOOL windowed)
{
	BeginDebugMemoryBlock

	HRESULT res;

	res = GraphicDevice::GetInstance()->Initialize(hWnd, width, height, windowed);
	if (FAILED(res))
	{
		GraphicDevice::GetInstance()->Release();
		return E_FAIL;
	}

	CentralTimeElement::GetInstance()->Initialize(144, 50);

	PhysicsDevice::GetInstance()->Initialize();

	BuiltIn::MakeBuiltInResources();

	m_initialized = true;

	srand(unsigned int(time(NULL)));

	return S_OK;
}

HRESULT EngineWorld::WindowProcedure(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!m_initialized)
		return E_FAIL;

	Input::GetInstance()->WindowProcedure(message, wParam, lParam);

	return S_OK;
}

HRESULT EngineWorld::Step()
{
	if (!m_initialized)
		return E_FAIL;

	auto centralTime = CentralTimeElement::GetInstance();

	unsigned int update = centralTime->UpdateAccumulate();
	unsigned int fixedUpdate = centralTime->FixedUpdateAccumulate();

	if (update + fixedUpdate > 0)
	{
		bool sceneChanged = false;
		if (update > 0)
		{
			sceneChanged = SceneManager::GetInstance()->TryChangeScene(nullptr);
		}

		//if (sceneChanged)
		//{
		//	centralTime->Reset();
		//}

		Scene* scene = SceneManager::GetCurrentScene();

		if (!scene)
			return S_OK;

		bool withDestroyPrepare = fixedUpdate > 0;
		scene->StepPrepare(withDestroyPrepare);

		scene->StepStart();

		if (fixedUpdate > 0)
		{
			if (fixedUpdate > 3)
				fixedUpdate = 3;

			auto physicsDevice = PhysicsDevice::GetInstance();
			for (unsigned int i = 0; i < fixedUpdate; ++i)
			{
				scene->StepBeginPhysicsSimulate();

				physicsDevice->Step(centralTime->GetFixedUpdateDeltaTime());

				scene->StepEndPhysicsSimulate();

				physicsDevice->Notify();

				scene->StepDestroyObjects();

				scene->StepFixedUpdate();
			}
		}

		if (update > 0)
		{
			scene->StepUpdate();

			Input::GetInstance()->SetUsed();
		}

		GraphicDevice* graphicDevice = GraphicDevice::GetInstance();
		IDirect3DDevice9* device = graphicDevice->GetDevice();
		Camera* mainCamera = Camera::GetMainCamera();

		graphicDevice->BeginRender();
		graphicDevice->GetRenderProcess()->ClearRenderTargets();
		scene->StepBeginRender();
		graphicDevice->GetRenderProcess()->Process();
		graphicDevice->EndRender();

		++m_fpsCount;
		m_fpsCheckElapsed += centralTime->GetUpdateDeltaTime();

		if (m_fpsCheckElapsed > 1.0f)
		{
			cout << m_fpsCount << endl;
			m_fpsCount = 0;
			m_fpsCheckElapsed = 0;
		}
	}

	return S_OK;
}

HRESULT EngineWorld::Release()
{
	SceneManager::UnloadAllScenes();

	ResourceManager::GetInstance()->ReleaseAllResources();

	GraphicDevice::GetInstance()->Release();

	PhysicsDevice::GetInstance()->Release();

	return S_OK;
}

bool EngineWorld::IsInitialized() const
{
	return m_initialized;
}
