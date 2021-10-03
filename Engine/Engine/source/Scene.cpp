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

	return go;
}

GameObject * Scene::FindGameObject(const wstring & name) const
{
	for (auto& pair : m_gameObjects)
	{
		auto& list = pair.second;

		for (auto& gameObject : list)
		{
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
			if (!gameObject->isWake)
				continue;

			if (gameObject->name == name)
				v.push_back(gameObject);
		}
	}

	return v;
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
	for (auto& pair : m_gameObjects)
	{
		auto& list = pair.second;

		for (auto& gameObject : list)
		{
			gameObject->Destroy();
			SafeDeleteInline(gameObject);
		}
		list.clear();
	}
	m_gameObjects.clear();
}

void Scene::Prepare()
{
	m_componentExecutioner->Prepare();
}

void Scene::StartStep()
{
	m_componentExecutioner->ExecuteStart();
}

void Scene::BeginPhysicsSimulateStep()
{
	m_componentExecutioner->ExecuteBeginPhysicsSimulate();
}

void Scene::EndPhysicsSimulateStep()
{
	m_componentExecutioner->ExecuteEndPhysicsSimulate();
}

void Scene::FixedUpdateStep()
{
	m_componentExecutioner->ExecuteFixedUpdate();
}

void Scene::UpdateStep()
{
	m_componentExecutioner->ExecuteUpdate();
}

void Scene::RenderStep()
{
	m_componentExecutioner->ExecuteRender();
}
