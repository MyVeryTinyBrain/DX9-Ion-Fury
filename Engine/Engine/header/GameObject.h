#pragma once

#include "SceneObject.h"

class GameObject : public SceneObject
{
public:

	friend class Scene;

	friend class Transform;

	friend class Component;

	friend class ComponentExecutioner;

private:

	GameObject(class Scene* regionScene, const tag_t& tag = L"");

	virtual ~GameObject();

public:

	class Transform* GetTransform() const;

	Ref<class Transform> GetRefTransform() const;

	void SetActiveSelf(bool active);

	bool IsActiveSelf() const;

	bool IsActiveInTree() const;

	bool IsWake() const;

	DefineGetReferenceTo(GameObject);

	void SetTag(const tag_t& tag);

	const tag_t& GetTag() const;

	class Scene* GetRegionScene() const;

	__declspec(property(get = GetTransform)) class Transform* transform;

	__declspec(property(get = GetRefTransform)) Ref<class Transform> refTransform;

	__declspec(property(get = IsActiveSelf, put = SetActiveSelf)) bool activeSelf;

	__declspec(property(get = IsActiveInTree)) bool activeInTree;

	__declspec(property(get = IsWake)) bool isWake;

	__declspec(property(get = GetTag, put = SetTag)) const tag_t& tag;

	__declspec(property(get = GetRegionScene, put = SetRegionScene)) class Scene* regionScene;

public:

	template <class T>
	T* AddComponent();

	template <class T>
	bool RemoveComponent();

	bool RemoveComponent(class Component* component);

	template <class T>
	T* GetComponent();

	template <class T>
	std::vector<T*> GetComponents();

	template <class T>
	T* GetComponentInChild();

	template <class T>
	std::vector<T*> GetComponentsInChild();

public:

	Delegate<void(GameObject*)> OnChangedTagCallback;

	Delegate<void(bool)> OnChangeWakeCallback;

private:

	void SetupTransform();

	void OnChangeWake(bool isWake);

	virtual void OnDestroy() override;

private:

	void SetRegionScene(class Scene* scene);

	ComponentVector& GetComponentReferences();

private:

	class Scene* m_regionScene = nullptr;

	tag_t m_tag = L"";

	ComponentVector m_components;
};

#include "GameObject.hpp"
