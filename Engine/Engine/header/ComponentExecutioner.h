#pragma once

#include "ComponentDefine.h"

class Component;
class Scene;
class GameObject;

class ComponentExecutioner
{
	enum class PrepareResult { None, Destroy, Execution };

public:

	ComponentExecutioner(Scene* regionScene);

	~ComponentExecutioner();

public:

	void Prepare();

	void ExecuteStart();

	void ExecuteBeginPhysicsSimulate();

	void ExecuteEndPhysicsSimulate();

	void ExecuteFixedUpdate();

	void ExecuteUpdate();

	void ExecuteRender();

	void ClearExecuteTargets();

	void ClearDestroyTargets();

private:

	PrepareResult PrepareGameObjectMap(GameObjectMap& gameObjectMap);

	PrepareResult PrepareGameObjectList(GameObjectList& gameObjectList);

	PrepareResult PrepareGameObject(GameObject* gameObject);

	PrepareResult PrepareComponent(Component* component);

	void SortExecutionTargetsByExecutionOrder();

private:

	Scene* m_regionScene;

	using ExecutionTargets = std::vector<Component*>;

	using DeleteTargetGameObjecs = std::vector<GameObject*>;

	using DeleteTargetComponents = std::vector<Component*>;

	DeleteTargetGameObjecs m_destroyTargetGameObjects;

	DeleteTargetComponents m_destroyTargetComponents;

	ExecutionTargets ComponentCallFlag(Start);

	ExecutionTargets ComponentCallFlag(BeginPhysicsSimulate);

	ExecutionTargets ComponentCallFlag(EndPhysicsSimulate);

	ExecutionTargets ComponentCallFlag(FixedUpdate);

	ExecutionTargets ComponentCallFlag(LateFixedUpdate);

	ExecutionTargets ComponentCallFlag(AnimationUpdate);

	ExecutionTargets ComponentCallFlag(Update);

	ExecutionTargets ComponentCallFlag(LateUpdate);

	ExecutionTargets ComponentCallFlag(BeginRender);

	ExecutionTargets ComponentCallFlag(BeforeRender);

	ExecutionTargets ComponentCallFlag(Render);

	ExecutionTargets ComponentCallFlag(AfterRender);

	ExecutionTargets ComponentCallFlag(EndRender);
};

