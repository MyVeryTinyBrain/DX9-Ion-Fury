#pragma once

#include "BaseObject.h"

class Scene abstract : public BaseObject, public IClonable
{
public:

	friend class GameObject;

	friend class SceneManager;

protected:

	Scene();

	virtual ~Scene();

public:

	virtual IClonable* Clone() = 0;

protected:

	virtual void OnLoad(Scene* beforeScene) = 0;

	virtual void OnUnload(Scene* nextScene) = 0;

public:

	class GameObject* CreateGameObject(const tag_t& tag = L"");

	class GameObject* FindGameObject(const wstring& name) const;

	std::vector<class GameObject*> FindGameObjects(const wstring& name) const;

	std::vector<class GameObject*> FindGameObjectsWithTag(const wstring& tag) const;

	GameObjectMap& GetGameObjectReferences();

private:

	void InsertGameObject(class GameObject* gameObject);

	void ReplaceGameObject(class GameObject* gameObject, const tag_t& beforeTag);

	void RemoveGameObject(class GameObject* gameObject, const tag_t& tag);

	void DeleteAllGameObjects();

public: // Should change to private

	void Prepare();

	void StartStep();

	void BeginPhysicsSimulateStep();

	void EndPhysicsSimulateStep();

	void FixedUpdateStep();

	void UpdateStep();

	void RenderStep();

private:

	GameObjectMap m_gameObjects;

	class ComponentExecutioner* m_componentExecutioner;
};

