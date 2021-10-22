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
	// Scene�� �ܺο��� DeleteAllGameObjects�� ȣ���մϴ�.

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
		// ���� Ű �����ȿ� ���ӿ�����Ʈ�� �������� �ʰ� �Ǹ�
		// ���� Ű ������ ����ϴ�.
		m_gameObjects.erase(find_it_in_map);
	}
}

void Scene::DeleteAllGameObjects()
{
	// ��� ���ӿ�����Ʈ�� Destroy�� �켱 ȣ���մϴ�.
	// �̿� ���� ��� ������Ʈ���� Destroy�� ȣ���մϴ�.
	for (auto& pair : m_gameObjects)
	{
		auto& list = pair.second;

		for (auto& gameObject : list)
		{
			gameObject->Destroy();
		}
	}

	// ��� ������Ʈ���� OnDestory �۾��� ���� ���Ŀ� ������ ���ӿ�����Ʈ�� �����ϰ� ����Ʈ�� ���ϴ�.
	// ������Ʈ�� OnDestroy �������� �ٸ� ������Ʈ�� ���ӿ�����Ʈ�� ������ �� �ֱ� �����Դϴ�.
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
