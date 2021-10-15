#include "EngineBase.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"

ImplementSingletone(SceneManager);

#define Instance	(g_instance)

SceneManager::~SceneManager()
{
	UnloadAllScenes();
}

void SceneManager::ChangeScene(Scene * nextScene) 
{
	// 이미 존재하는 인스턴스로 변경하려는 경우 종료합니다.
	if (Instance.m_current == nextScene) return;

	Instance.ResetNextScenes();
	Instance.m_next = nextScene;
}

void SceneManager::ReloadScene()
{
	Scene* current = GetCurrentScene();

	if (!current) return;

	Scene* cloneScene = dynamic_cast<Scene*>(current->Clone());

	if (!cloneScene) return;

	ChangeScene(cloneScene);
}

void SceneManager::UnloadAllScenes()
{
	Scene* current = Instance.m_current;

	if (current)
	{
		current->OnUnload(nullptr);
		current->DeleteAllGameObjects();
	}

	Instance.ResetNextScenes();

	SafeDeleteInline(Instance.m_current);
}

Scene * SceneManager::GetCurrentScene()
{
	return Instance.m_current;
}

bool SceneManager::TryChangeScene(Scene ** outBeforeScenes)
{
	if (outBeforeScenes)
		*outBeforeScenes = m_current;

	if (m_next) 
	{
		if (m_current)
		{
			m_current->OnUnload(m_next);
			m_current->DeleteAllGameObjects();
			ResourceManager::GetInstance()->ReleaseUnsharedResources();
		}

		Scene* beforeScene = m_current;

		m_current = m_next;

		m_next->OnLoad(beforeScene);

		SafeDeleteInline(beforeScene);

		m_next = nullptr;

		return true;
	}

	return false;
}

void SceneManager::ResetNextScenes()
{
	SafeDeleteInline(m_next);
}
