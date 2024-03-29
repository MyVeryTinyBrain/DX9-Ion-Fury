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

	void ExecutePrepare(bool withDestroyPrepare);

	void ExecuteStart();

	void ExecuteBeginPhysicsSimulate();

	void ExecuteEndPhysicsSimulate();

	void ExecuteDestroy(GameObjectMap& gameObjectMap);

	void ExecuteFixedUpdate();

	void ExecuteUpdate();

	void ExecuteBeginRender();

private:

	void ClearExecuteTargets();

private:

	PrepareResult PrepareGameObjectMap(GameObjectMap& gameObjectMap, bool withDestroyPrepare);

	PrepareResult PrepareGameObjectList(GameObjectList& gameObjectList, bool withDestroyPrepare);

	PrepareResult PrepareGameObject(GameObject* gameObject, bool withDestroyPrepare);

	PrepareResult PrepareComponent(Component* component, bool withDestroyPrepare);

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

	ExecutionTargets ComponentCallFlag(BeginFixedUpdate);

	ExecutionTargets ComponentCallFlag(FixedUpdate);

	ExecutionTargets ComponentCallFlag(LateFixedUpdate);

	ExecutionTargets ComponentCallFlag(FixedUpdateCheck);

	ExecutionTargets ComponentCallFlag(BeginUpdate);

	ExecutionTargets ComponentCallFlag(AnimationUpdate);

	ExecutionTargets ComponentCallFlag(Update);

	ExecutionTargets ComponentCallFlag(LateUpdate);

	ExecutionTargets ComponentCallFlag(UpdateCheck);

	ExecutionTargets ComponentCallFlag(BeginRender);
};

