#include "EngineBase.h"
#include "ComponentExecutioner.h"
#include "ComponentExecutionerDefine.h"
#include "Scene.h"
#include "GameObject.h"

ComponentExecutioner::ComponentExecutioner(Scene * regionScene)
{
	m_regionScene = regionScene;
}

ComponentExecutioner::~ComponentExecutioner()
{
}

void ComponentExecutioner::ExecutePrepare(bool withDestroyPrepare)
{
	ClearExecuteTargets();

	GameObjectMap& gameObjectMap = m_regionScene->GetGameObjectReferences();

	PrepareGameObjectMap(gameObjectMap, withDestroyPrepare);

	SortExecutionTargetsByExecutionOrder();
}

void ComponentExecutioner::ExecuteStart()
{
	ExecuteByOrder(Start);
}

void ComponentExecutioner::ExecuteBeginPhysicsSimulate()
{
	ExecuteByOrder(BeginPhysicsSimulate);
}

void ComponentExecutioner::ExecuteEndPhysicsSimulate()
{
	ExecuteByOrder(EndPhysicsSimulate);
}

void ComponentExecutioner::ExecuteDestroy(GameObjectMap& gameObjectMap)
{
	// �ı��Ǿ�� �� ������Ʈ���� ��� �ı��մϴ�.
	for (auto& destroyTargetComponent : m_destroyTargetComponents)
	{
		auto golist_it = gameObjectMap.find(destroyTargetComponent->gameObject->tag);
		GameObjectList& golist = golist_it->second;
		auto go_it = FindInContainer(golist, destroyTargetComponent->gameObject);
		GameObject* go = *go_it;
		auto comp_it = FindInContainer(go->m_components, destroyTargetComponent);

		// ���ӿ�����Ʈ�� ������Ʈ ����Ʈ���� �����մϴ�.
		go->m_components.erase(comp_it);

		// ������Ʈ�� �ı��մϴ�.
		Component* comp = destroyTargetComponent;
		SafeDeleteInline(comp);
	}

	// �ı��Ǿ�� �� ���ӿ�����Ʈ���� ��� �ı��մϴ�.
	for (auto& destroyTargetGameObject : m_destroyTargetGameObjects)
	{
		auto golist_it = gameObjectMap.find(destroyTargetGameObject->tag);
		GameObjectList& golist = golist_it->second;
		auto go_it = FindInContainer(golist, destroyTargetGameObject);

		// ���ӿ�����Ʈ ����Ʈ���� �����մϴ�.
		golist.erase(go_it);

		// ���� ����Ʈ�� ����ִٸ� ���� Ű ������ ����ϴ�.
		if (golist.empty())
		{
			gameObjectMap.erase(golist_it);
		}

		// ���ӿ�����Ʈ�� �ı��մϴ�.
		GameObject* go = destroyTargetGameObject;
		SafeDeleteInline(go);
	}

	// �ı� ��� ����Ʈ���� ���ϴ�.
	m_destroyTargetComponents.clear();
	m_destroyTargetGameObjects.clear();
}

void ComponentExecutioner::ExecuteFixedUpdate()
{
	ExecuteByOrder(FixedUpdate);

	ExecuteByOrder(LateFixedUpdate);
}

void ComponentExecutioner::ExecuteUpdate()
{
	ExecuteByOrder(AnimationUpdate);

	ExecuteByOrder(Update);

	ExecuteByOrder(LateUpdate);
}

void ComponentExecutioner::ExecuteBeginRender()
{
	ExecuteByOrder(BeginRender);
}

void ComponentExecutioner::ClearExecuteTargets()
{
	ComponentCallFlag(Start).clear();

	ComponentCallFlag(BeginPhysicsSimulate).clear();

	ComponentCallFlag(EndPhysicsSimulate).clear();

	ComponentCallFlag(FixedUpdate).clear();

	ComponentCallFlag(LateFixedUpdate).clear();

	ComponentCallFlag(AnimationUpdate).clear();

	ComponentCallFlag(Update).clear();

	ComponentCallFlag(LateUpdate).clear();

	ComponentCallFlag(BeginRender).clear();
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareGameObjectMap(GameObjectMap & gameObjectMap, bool withDestroyPrepare)
{
	for (auto it_pair = gameObjectMap.begin(); it_pair != gameObjectMap.end();)
	{
		auto& list = it_pair->second;

		PrepareResult prepareGameObjectList = PrepareGameObjectList(list, withDestroyPrepare);

		++it_pair;
	}

	return PrepareResult::None;
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareGameObjectList(GameObjectList & gameObjectList, bool withDestroyPrepare)
{
	for (auto it_gameObject = gameObjectList.begin(); it_gameObject != gameObjectList.end();)
	{
		GameObject* gameObject = *it_gameObject;

		PrepareResult prepareGameObject = PrepareGameObject(gameObject, withDestroyPrepare);

		if (prepareGameObject == PrepareResult::Destroy)
		{
			if (withDestroyPrepare)
			{
				m_destroyTargetGameObjects.push_back(gameObject);
			}

			++it_gameObject;

			continue;
		}

		++it_gameObject;
	}

	return PrepareResult::None;
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareGameObject(GameObject * gameObject, bool withDestroyPrepare)
{
	if (gameObject->IsShouldDestroy())
	{
		return PrepareResult::Destroy;
	}

	if (!gameObject->transform->isWake)
	{
		return PrepareResult::None;
	}

	ComponentVector& components = gameObject->GetComponentReferences();

	for (auto it_component = components.begin(); it_component != components.end();)
	{
		Component* component = *it_component;

		PrepareResult prepareComponent = PrepareComponent(component, withDestroyPrepare);

		if (prepareComponent == PrepareResult::Destroy)
		{
			if (withDestroyPrepare)
			{
				m_destroyTargetComponents.push_back(component);
			}

			++it_component;

			continue;
		}

		++it_component;
	}

	return PrepareResult::Execution;
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareComponent(Component * component, bool withDestroyPrepare)
{
	if (component->IsShouldDestroy())
	{
		return PrepareResult::Destroy;
	}

	if (!component->isWake)
	{
		return PrepareResult::None;
	}

	TryAddToExecutionTargetAndSetFalse(component, Start);

	TryAddToExecutionTarget(component, BeginPhysicsSimulate);

	TryAddToExecutionTarget(component, EndPhysicsSimulate);

	TryAddToExecutionTarget(component, FixedUpdate);

	TryAddToExecutionTarget(component, LateFixedUpdate);

	TryAddToExecutionTarget(component, AnimationUpdate);

	TryAddToExecutionTarget(component, Update);

	TryAddToExecutionTarget(component, LateUpdate);

	TryAddToExecutionTarget(component, BeginRender);

	return PrepareResult::Execution;
}

void ComponentExecutioner::SortExecutionTargetsByExecutionOrder()
{
	SortByExecutionOrder(Start);

	SortByExecutionOrder(BeginPhysicsSimulate);

	SortByExecutionOrder(EndPhysicsSimulate);

	SortByExecutionOrder(FixedUpdate);

	SortByExecutionOrder(LateFixedUpdate);

	SortByExecutionOrder(AnimationUpdate);

	SortByExecutionOrder(Update);

	SortByExecutionOrder(LateUpdate);

	SortByExecutionOrder(BeginRender);
}
