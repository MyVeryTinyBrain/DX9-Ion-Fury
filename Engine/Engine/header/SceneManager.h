#pragma once

class Scene;

class SceneManager
{
private:

	DeclareSingletone(SceneManager);

	SceneManager() = default;

	~SceneManager();

public:

	static void ChangeScene(Scene* nextScene);

	static void ReloadScene();

	static void UnloadAllScenes();

	static Scene* GetCurrentScene();

public:

	bool TryChangeScene(Scene** outBeforeScenes);

private:

	void ResetNextScenes();

private:

	Scene* m_current = nullptr;

	Scene* m_next = nullptr;

	//Scene* m_asyncNext = nullptr;

	//Scene* m_asyncMergeNext = nullptr;
};

