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
	ClearDestroyTargets();

	ClearExecuteTargets();
}

void ComponentExecutioner::Prepare()
{
	ClearDestroyTargets();

	ClearExecuteTargets();

	GameObjectMap& gameObjectMap = m_regionScene->GetGameObjectReferences();

	PrepareGameObjectMap(gameObjectMap);

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
#include "GraphicDevice.h"
void ComponentExecutioner::ExecuteRender()
{
	ExecuteByOrder(BeginRender);

	ExecuteByOrder(BeforeRender);

	ExecuteByOrder(Render);

	ExecuteByOrder(AfterRender);

	ExecuteByOrder(EndRender);
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

	ComponentCallFlag(BeforeRender).clear();

	ComponentCallFlag(Render).clear();

	ComponentCallFlag(AfterRender).clear();

	ComponentCallFlag(EndRender).clear();
}

void ComponentExecutioner::ClearDestroyTargets()
{
	for (auto& destroyTargetGameObject : m_destroyTargetGameObjects)
		SafeDeleteInline(destroyTargetGameObject);
	m_destroyTargetGameObjects.clear();

	for (auto& destroyTargetComponent : m_destroyTargetComponents)
		SafeDeleteInline(destroyTargetComponent);
	m_destroyTargetComponents.clear();
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareGameObjectMap(GameObjectMap & gameObjectMap)
{
	for (auto it_pair = gameObjectMap.begin(); it_pair != gameObjectMap.end();)
	{
		auto& list = it_pair->second;

		PrepareResult prepareGameObjectList = PrepareGameObjectList(list);

		if (prepareGameObjectList == PrepareResult::Destroy)
		{
			it_pair = gameObjectMap.erase(it_pair);

			continue;
		}

		++it_pair;
	}

	return PrepareResult::None;
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareGameObjectList(GameObjectList & gameObjectList)
{
	for (auto it_gameObject = gameObjectList.begin(); it_gameObject != gameObjectList.end();)
	{
		GameObject* gameObject = *it_gameObject;

		PrepareResult prepareGameObject = PrepareGameObject(gameObject);

		if (prepareGameObject == PrepareResult::Destroy)
		{
			it_gameObject = gameObjectList.erase(it_gameObject);

			m_destroyTargetGameObjects.push_back(gameObject);

			continue;
		}

		++it_gameObject;
	}

	if (gameObjectList.empty())
		return PrepareResult::Destroy;
	else
		return PrepareResult::None;
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareGameObject(GameObject * gameObject)
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

		PrepareResult prepareComponent = PrepareComponent(component);

		if (prepareComponent == PrepareResult::Destroy)
		{
			it_component = components.erase(it_component);

			m_destroyTargetComponents.push_back(component);

			continue;
		}

		++it_component;
	}

	return PrepareResult::Execution;
}

ComponentExecutioner::PrepareResult ComponentExecutioner::PrepareComponent(Component * component)
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

	TryAddToExecutionTarget(component, BeforeRender);

	TryAddToExecutionTarget(component, Render);

	TryAddToExecutionTarget(component, AfterRender);

	TryAddToExecutionTarget(component, EndRender);

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

	SortByExecutionOrder(BeforeRender);

	SortByExecutionOrder(Render);

	SortByExecutionOrder(AfterRender);

	SortByExecutionOrder(EndRender);
}
