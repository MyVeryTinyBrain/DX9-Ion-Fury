#include "EngineBase.h"
#include "Scene.h"
#include "GameObject.h"
#include "ComponentExecutioner.h"

Scene::Scene()
{
	m_componentExecutioner = new ComponentExecutioner(this);
}

Scene::~Scene()
{
	// Scene의 외부에서 DeleteAllGameObjects를 호출합니다.

	SafeDelete(m_componentExecutioner);
}

GameObject * Scene::CreateGameObject(const tag_t& tag)
{
	GameObject* go = new GameObject(this, tag);

	return go;
}

GameObject* Scene::CreateGameObjectToChild(class Transform* parent, const tag_t& tag)
{
	GameObject* go = new GameObject(this, tag);
	go->transform->parent = parent;
	go->transform->localPosition = Vec3::zero();
	go->transform->localRotation = Quat::Identity();
	go->transform->localScale = Vec3::one();
	return go;
}

GameObject * Scene::FindGameObject(const wstring & name) const
{
	for (auto& pair : m_gameObjects)
	{
		auto& list = pair.second;

		for (auto& gameObject : list)
		{
			if (gameObject->IsShouldDestroy())
				continue;

			if (!gameObject->isWake)
				continue;

			if (gameObject->name == name)
				return gameObject;
		}
	}

	return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjects(const wstring & name) const
{
	std::vector<GameObject*> v;

	for (auto& pair : m_gameObjects)
	{
		auto& list = pair.second;

		for (auto& gameObject : list)
		{
			if (gameObject->IsShouldDestroy())
				continue;

			if (!gameObject->isWake)
				continue;

			if (gameObject->name == name)
				v.push_back(gameObject);
		}
	}

	return v;
}

class GameObject* Scene::FindGameObjectWithTag(const wstring& tag) const
{
	auto find_it = m_gameObjects.find(tag);

	if (find_it == m_gameObjects.end())
		return nullptr;

	auto& list = find_it->second;

	for (auto& gameObject : list)
	{
		if (gameObject->IsShouldDestroy())
			continue;

		if (!gameObject->isWake)
			continue;

		if (gameObject->tag == tag)
			return gameObject;
	}

	return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjectsWithTag(const wstring & tag) const
{
	std::vector<GameObject*> v;

	auto find_it = m_gameObjects.find(tag);

	if (find_it == m_gameObjects.end()) 
		return v;

	auto& list = find_it->second;

	for (auto& gameObject : list)
	{
		if (gameObject->IsShouldDestroy())
			continue;

		if (!gameObject->isWake)
			continue;

		if (gameObject->tag == tag)
			v.push_back(gameObject);
	}

	return v;
}

GameObjectMap& Scene::GetGameObjectReferences()
{
	return m_gameObjects;
}

void Scene::InsertGameObject(GameObject* gameObject)
{
	m_gameObjects[gameObject->tag].push_back(gameObject);
}

void Scene::ReplaceGameObject(GameObject* gameObject, const tag_t& beforeTag)
{
	RemoveGameObject(gameObject, beforeTag);

	InsertGameObject(gameObject);
}

void Scene::RemoveGameObject(GameObject* gameObject, const tag_t& tag)
{
	auto find_it_in_map = m_gameObjects.find(tag);

	GameObjectList& gameObjectList = find_it_in_map->second;

	auto find_it_in_list = FindInContainer(gameObjectList, gameObject);

	gameObjectList.erase(find_it_in_list);

	if (gameObjectList.empty())
	{
		// 맵의 키 공간안에 게임오브젝트가 존재하지 않게 되면
		// 맵의 키 공간을 지웁니다.
		m_gameObjects.erase(find_it_in_map);
	}
}

void Scene::DeleteAllGameObjects()
{
	// 모든 게임오브젝트에 Destroy를 우선 호출합니다.
	// 이에 따라 모든 컴포넌트들이 Destroy를 호출합니다.
	for (auto& pair : m_gameObjects)
	{
		auto& list = pair.second;

		for (auto& gameObject : list)
		{
			gameObject->Destroy();
		}
	}

	// 모든 컴포넌트들이 OnDestory 작업을 끝낸 이후에 실제로 게임오브젝트를 삭제하고 리스트를 비웁니다.
	// 컴포넌트의 OnDestroy 구현에서 다른 컴포넌트나 게임오브젝트를 참조할 수 있기 때문입니다.
	for (auto& pair : m_gameObjects)
	{
		auto& list = pair.second;

		for (auto& gameObject : list)
		{
			SafeDeleteInline(gameObject);
		}
		list.clear();
	}
	m_gameObjects.clear();
}

void Scene::StepPrepare(bool withDestroyPrepare)
{
	m_componentExecutioner->ExecutePrepare(withDestroyPrepare);
}

void Scene::StepStart()
{
	m_componentExecutioner->ExecuteStart();
}

void Scene::StepBeginPhysicsSimulate()
{
	m_componentExecutioner->ExecuteBeginPhysicsSimulate();
}

void Scene::StepEndPhysicsSimulate()
{
	m_componentExecutioner->ExecuteEndPhysicsSimulate();
}

void Scene::StepDestroyObjects()
{
	m_componentExecutioner->ExecuteDestroy(m_gameObjects);
}

void Scene::StepFixedUpdate()
{
	m_componentExecutioner->ExecuteFixedUpdate();
}

void Scene::StepUpdate()
{
	m_componentExecutioner->ExecuteUpdate();

	OnUpdate();
}

void Scene::StepBeginRender()
{
	m_componentExecutioner->ExecuteBeginRender();
}
