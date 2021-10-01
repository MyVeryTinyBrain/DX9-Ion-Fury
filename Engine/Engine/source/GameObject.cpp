#include "EngineBase.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Scene.h"

#define TRANSFORM_INDEX			(0)
#define TRANSFORM				((Transform*)m_components[TRANSFORM_INDEX])
#define TRANSFORM_REF			(TRANSFORM->GetReferenceTo<Transform>())

GameObject::GameObject(Scene* regionScene, const tag_t& tag) : SceneObject()
{
	m_tag = tag;

	m_regionScene = regionScene;

	m_regionScene->InsertGameObject(this);

	SetupTransform();
}

GameObject::~GameObject()
{
	Destroy();

	// 게임오브젝트가 삭제될 때에는 들고있는 모든 컴포넌트들을 삭제합니다.
	for (auto& component : m_components)
	{
		SafeDeleteInline(component);
	}
	m_components.clear();
}

Transform* GameObject::GetTransform() const
{
	return TRANSFORM;
}

Ref<Transform> GameObject::GetRefTransform() const
{
	return TRANSFORM_REF;
}

void GameObject::SetActiveSelf(bool active)
{
	transform->SetActiveSelf(active);
}

bool GameObject::IsActiveSelf() const
{
	return transform->IsActiveSelf();
}

bool GameObject::IsActiveInTree() const
{
	return transform->IsActiveInTree();
}

bool GameObject::IsWake() const
{
	return transform->isWake;
}

void GameObject::SetTag(const tag_t & tag)
{
	if (tag == m_tag) return;

	tag_t beforeTag = m_tag;

	m_tag = tag;

	m_regionScene->ReplaceGameObject(this, beforeTag);
}

const tag_t& GameObject::GetTag() const
{
	return m_tag;
}

Scene * GameObject::GetRegionScene() const
{
	return m_regionScene;
}

bool GameObject::RemoveComponent(Component * component)
{
	return false;
}

void GameObject::SetupTransform()
{
	// =============================================================================================
	// 트랜스폼 컴포넌트는 벡터의 0번째에 위치하게 됩니다.
	// 이 순서는 절대 변경될 수 없습니다.
	// 만약 트랜스폼에 Destroy 함수를 호출하는 경우에는 GameObject에 Destroy를 호출하는 것과 같습니다.
	// =============================================================================================

	Transform* transform = new Transform();
	transform->Initialize(this, transform);
	transform->OnChangeWakeCallback += Function<void(bool)>(this, &GameObject::OnChangeWake);
	m_components.push_back(transform);
}

void GameObject::OnChangeWake(bool isWake)
{
	OnChangeWakeCallback(isWake);
}

void GameObject::OnDestroy()
{
	transform->OnChangeWakeCallback -= Function<void(bool)>(this, &GameObject::OnChangeWake);

	for (auto& component : m_components)
	{
		// 실제 삭제와 리스트에서의 제거는 이곳에서 하지 않습니다.
		component->Destroy();
	}
}

void GameObject::SetRegionScene(Scene * scene)
{
	m_regionScene = scene;
}

ComponentVector& GameObject::GetComponentReferences()
{
	return m_components;
}
