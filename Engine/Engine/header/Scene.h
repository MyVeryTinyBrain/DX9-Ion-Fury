#pragma once

#include "BaseObject.h"

class Scene abstract : public BaseObject, public IClonable
{
public:

	friend class GameObject;

	friend class SceneManager;

	friend class EngineWorld;

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

	class GameObject* CreateGameObjectToChild(class Transform* parent, const tag_t& tag = L"");

	class GameObject* FindGameObject(const wstring& name) const;

	std::vector<class GameObject*> FindGameObjects(const wstring& name) const;

	class GameObject* FindGameObjectWithTag(const wstring& tag) const;

	std::vector<class GameObject*> FindGameObjectsWithTag(const wstring& tag) const;

	GameObjectMap& GetGameObjectReferences();

private:

	void InsertGameObject(class GameObject* gameObject);

	void ReplaceGameObject(class GameObject* gameObject, const tag_t& beforeTag);

	void RemoveGameObject(class GameObject* gameObject, const tag_t& tag);

	void DeleteAllGameObjects();

private: // Should change to private

	void StepPrepare(bool withDestroyPrepare);

	void StepStart();

	void StepBeginPhysicsSimulate();

	void StepEndPhysicsSimulate();

	void StepDestroyObjects();

	void StepFixedUpdate();

	void StepUpdate();

	void StepBeginRender();

private:

	GameObjectMap m_gameObjects;

	class ComponentExecutioner* m_componentExecutioner;
};

