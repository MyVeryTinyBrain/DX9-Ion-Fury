#pragma once

#include "SceneObject.h"
#include "ComponentDefine.h"

class Component abstract : public SceneObject
{
	friend class GameObject;

	friend class Transform;

	friend class ComponentExecutioner;

protected:

	// 컴포넌트가 생성된 이후 바로 호출됩니다.
	DefineComponentFunction(Awake);

	DefineComponentFunction(Start);

	DefineComponentFunction(BeginPhysicsSimulate);

	DefineComponentFunction(EndPhysicsSimulate);

	DefineComponentFunction(BeginFixedUpdate);

	DefineComponentFunction(FixedUpdate);

	DefineComponentFunction(LateFixedUpdate);

	DefineComponentFunction(FixedUpdateCheck);

	DefineComponentFunction(BeginUpdate);

	DefineComponentFunction(AnimationUpdate);

	DefineComponentFunction(Update);

	DefineComponentFunction(LateUpdate);

	DefineComponentFunction(UpdateCheck);

	DefineComponentFunction(BeginRender);

	// 컴포넌트가 활성화 상태로 변경되었을 때 호출됩니다.
	// 컴포넌트가 생성되어 Awake 호출이 완료된 후에도 호출됩니다.
	DefineComponentFunction(OnWake);

	// 컴포넌트가 비활성화 상태로 변경되었을 때 호출됩니다.
	DefineComponentFunction(OnSleep);

	// 컴포넌트의 Destroy 함수가 처음 호출되었을 때 호출됩니다.
	DefineComponentFunction(OnDestroy);

public:

	class GameObject* GetGameObject() const;

	Ref<class GameObject> GetRefGameObject() const;

	class Transform* GetTransform() const;

	Ref<class Transform> GetRefTransform() const;

	void SetEnable(bool enable);

	bool IsEnable() const;

	bool IsWake() const;

	DefineGetReferenceTo(Component);

	class GameObject* CreateGameObject(const tag_t& tag = L"");

	class GameObject* CreateGameObjectToChild(Transform* parent, const tag_t& tag = L"");

	class GameObject* FindGameObject(const wstring& name) const;

	std::vector<class GameObject*> FindGameObjects(const wstring& name) const;

	std::vector<class GameObject*> FindGameObjectsWithTag(const wstring& tag) const;

	__declspec(property(get = GetGameObject)) class GameObject* gameObject;

	__declspec(property(get = GetRefGameObject)) Ref<class GameObject> refGameObject;

	__declspec(property(get = GetTransform)) class Transform* transform;

	__declspec(property(get = GetRefTransform)) Ref<class Transform> refTransform;

	__declspec(property(get = IsEnable, put = SetEnable)) bool enable;

	__declspec(property(get = IsWake)) bool isWake;

private:

	// Call once when created by GameObject
	void Initialize
	(
		class GameObject* gameObject,
		class Transform* transform
	);

protected:

	Component();

	virtual ~Component();

private:

	void OnEnableChanged();

	virtual void OnBeforeDestroy() override;

public:

	Delegate<void(bool)> OnChangeWakeCallback;

private:

	class GameObject* m_gameObject = nullptr;

	class Transform* m_transform = nullptr;

	bool m_enable = true;

	bool m_beforeWake = true;
};

