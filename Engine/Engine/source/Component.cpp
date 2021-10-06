#include "EngineBase.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

GameObject* Component::GetGameObject() const
{
	return m_gameObject;
}

Ref<GameObject> Component::GetRefGameObject() const
{
	return m_gameObject->refGameObject;
}

Transform* Component::GetTransform() const
{
	return m_transform;
}

Ref<Transform> Component::GetRefTransform() const
{
	return m_transform->refTransform;
}

void Component::SetEnable(bool enable)
{
	if (m_enable == enable)
		return;

	m_enable = enable;

	OnEnableChanged();
}

bool Component::IsEnable() const
{
	return m_enable;
}

bool Component::IsWake() const
{
	return enable && transform->activeSelf && transform->activeInTree;
}

GameObject * Component::CreateGameObject(const tag_t& tag)
{
	GameObject* go = new GameObject(gameObject->regionScene, tag);

	return go;
}

GameObject* Component::CreateGameObjectToChild(Transform* parent, const tag_t& tag)
{
	GameObject* go = new GameObject(gameObject->regionScene, tag);
	go->transform->parent = parent;
	go->transform->localPosition = Vec3::zero();

	return go;
}

GameObject* Component::FindGameObject(const wstring& name) const
{
	return gameObject->regionScene->FindGameObject(name);
}

std::vector<class GameObject*> Component::FindGameObjects(const wstring& name) const
{
	return gameObject->regionScene->FindGameObjects(name);
}

std::vector<class GameObject*> Component::FindGameObjectsWithTag(const wstring& tag) const
{
	return gameObject->regionScene->FindGameObjectsWithTag(tag);
}

void Component::Initialize
(
	GameObject* gameObject, 
	Transform* transform
)
{
	m_gameObject = gameObject;
	m_transform = transform;

	ComponentSetCall(Awake);

	ComponentSetCall(Start);

	ComponentSetCall(BeginPhysicsSimulate);

	ComponentSetCall(EndPhysicsSimulate);

	ComponentSetCall(FixedUpdate);

	ComponentSetCall(LateFixedUpdate);

	ComponentSetCall(AnimationUpdate);

	ComponentSetCall(Update);

	ComponentSetCall(LateUpdate);

	ComponentSetCall(BeginRender);

	ComponentSetCall(BeforeRender);

	ComponentSetCall(AfterRender);

	ComponentSetCall(EndRender);

	//ComponentSetCall(OnWake);

	//ComponentSetCall(OnSleep);

	//ComponentSetCall(OnDestroy);

	if (ComponentCallFlag(Awake))
	{
		Awake();
		ComponentCallFlag(Awake) = false;
	}

	if (ComponentCallFlag(OnWake))
	{
		OnWake();
	}

	// enable = true;
}

Component::Component() : SceneObject()
{
}

Component::~Component()
{
}

void Component::OnEnableChanged()
{
	if (isWake == m_beforeWake) return;

	if (isWake)
	{
		OnWake();
	}
	else
	{
		OnSleep();
	}

	OnChangeWakeCallback(isWake);

	m_beforeWake = isWake;
}

void Component::OnBeforeDestroy()
{
	enable = false;
}
