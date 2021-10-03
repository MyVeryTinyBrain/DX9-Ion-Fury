#pragma once

#include "Component.h"

class Transform final : public Component
{
	friend class GameObject;

	enum class UpdateTransformArgument : unsigned int;

public:

	DefineGetReferenceTo(Transform);

public:

	void SetActiveSelf(bool active);

	bool IsActiveSelf() const;

	bool IsActiveInTree() const;

	void SetParent(Transform* parent);

	void DetachFromParent();

	void AddChild(Transform* child);

	void RemoveChild(Transform* child);

	Transform* GetRoot() const;

	Transform* GetParent() const;

	size_t GetChildCount() const;

	Transform* GetChild(index_t index) const;

	std::vector<Transform*> GetChilds() const;

	__declspec(property(get = IsActiveSelf, put = SetActiveSelf)) bool activeSelf;

	__declspec(property(get = IsActiveInTree)) bool activeInTree;

	__declspec(property(get = GetRoot)) Transform* root;

	__declspec(property(get = GetParent, put = SetParent)) Transform* parent;

	__declspec(property(get = GetChildCount)) size_t childCount;

public:

	void SetPosition(const Vec3& position);

	void SetRotation(const Quat& rotation);

	void SetEulerAngle(const Vec3& eulerAngle);

	void SetScale(const Vec3& scale);

	void SetLocalPosition(const Vec3& localPosition);

	void SetLocalRotation(const Quat& localRotation);

	void SetLocalEulerAngle(const Vec3& localEulerAngle);

	void SetLocalScale(const Vec3& localScale);

	const Vec3& GetPosition() const;

	const Quat& GetRotation() const;

	Vec3 GetEulerAngle() const;
	 
	const Vec3& GetScale() const;

	const Vec3& GetLocalPosition() const;

	const Quat& GetLocalRotation() const;

	Vec3 GetLocalEulerAngle() const;

	const Vec3& GetLocalScale() const;

	Mat4 GetLocalToWorldMatrix() const;

	Mat4 GetWorldToLocalMatrix() const;

	void SetRightDirection(const Vec3& right);
		 
	void SetUpDirection(const Vec3& up);
		 
	void SetForwardDirection(const Vec3& forward);

	Vec3 GetRightDirection() const;

	Vec3 GetUpDirection() const;

	Vec3 GetForwardDirection() const;

	__declspec(property(get = GetPosition, put = SetPosition)) const Vec3& position;

	__declspec(property(get = GetRotation, put = SetRotation)) const Quat& rotation;

	__declspec(property(get = GetEulerAngle, put = SetEulerAngle)) Vec3 eulerAngle;

	__declspec(property(get = GetScale, put = SetScale)) const Vec3& scale;
							  
	__declspec(property(get = GetLocalPosition, put = SetLocalPosition)) const Vec3& localPosition;
							  
	__declspec(property(get = GetLocalRotation, put = SetLocalRotation)) const Quat& localRotation;

	__declspec(property(get = GetLocalEulerAngle, put = SetLocalEulerAngle)) Vec3 localEulerAngle;
							  
	__declspec(property(get = GetLocalScale, put = SetLocalScale)) const Vec3& localScale;

	__declspec(property(get = GetLocalToWorldMatrix)) Mat4 localToWorld;

	__declspec(property(get = GetWorldToLocalMatrix)) Mat4 worldToLocal;

	__declspec(property(get = GetRightDirection, put = SetRightDirection)) Vec3 right;

	__declspec(property(get = GetUpDirection, put = SetUpDirection)) Vec3 up;

	__declspec(property(get = GetForwardDirection, put = SetForwardDirection)) Vec3 forward;

private:

	void UpdateActiveInTree();

	void UpdateChildWorldTransforms(const UpdateTransformArgument& args);

	void UpdateLocalTransform(const UpdateTransformArgument& args);

	void UpdateWorldTransform(const UpdateTransformArgument& args);

	void UpdateLocalPosition(const UpdateTransformArgument& args);

	void UpdateLocalRotation(const UpdateTransformArgument& args);

	void UpdateLocalScale(const UpdateTransformArgument& args);

	void UpdateWorldPosition(const UpdateTransformArgument& args);
			   
	void UpdateWorldRotation(const UpdateTransformArgument& args);
			   
	void UpdateWorldScale(const UpdateTransformArgument& args);

	OverrideComponentFunction(OnDestroy);

private: // Deleted Functions...

	void SetEnable(bool enable) = delete;

	bool IsEnable() const = delete;

	__declspec(property(get = IsEnable, put = SetEnable)) bool enable;

private:

	bool m_activeSelf = true;

	bool m_activeInTree = true;

	Transform* m_parent = nullptr;

	std::vector<Transform*> m_childs;

	Vec3 m_position = Vec3::zero();

	Quat m_rotation = Quat::Identity();

	Vec3 m_eulerAngle = Vec3::zero();

	Vec3 m_scale = Vec3::one();

	Vec3 m_localPosition = Vec3::zero();

	Quat m_localRotation = Quat::Identity();

	Vec3 m_localEulerAngle = Vec3::zero();

	Vec3 m_localScale = Vec3::one();

private:

	enum class UpdateTransformArgument : unsigned int
	{
		None = 0x00,
		FromEulerAngle = 0x01, 
	};
};

