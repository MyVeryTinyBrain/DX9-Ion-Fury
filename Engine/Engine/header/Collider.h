#pragma once

#include "Component.h"

class Collider : public Component
{
	friend class Rigidbody;

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(BeginPhysicsSimulate);

	OverrideComponentFunction(OnWake);

	OverrideComponentFunction(OnSleep);

	OverrideComponentFunction(OnDestroy);

public:

	bool IsTrigger() const;

	void SetTrigger(bool value);

	float GetFriction() const;

	void SetFriction(float value);

	float GetRestitution() const;

	void SetRestitution(float value);

	__declspec(property(get = IsTrigger, put = SetTrigger)) bool isTrigger;

	__declspec(property(get = GetFriction, put = SetFriction)) float friction;

	__declspec(property(get = GetRestitution, put = SetRestitution)) float restitution;

public:

	void ApplyTransform();

	void ApplyScale();

	void SetPosition(const Vec3& position);

	void SetLocalPosition(const Vec3& localPosition);

	void SetRotation(const Quat& rotation);

	void SetLocalRotation(const Quat& localRotation);

	void SetEulerAngle(const Vec3& eulerAngle);

	void SetLocalEulerAngle(const Vec3& localEulerAngle);

	void SetScale(const Vec3& scale);

	void SetLocalScale(const Vec3& localScale);

	class Rigidbody* GetRigidbody() const;

	__declspec(property(get = GetRigidbody)) class Rigidbody* rigidbody;

public:

	// 0 ~ 31 ������ ���̾� �ε����� ��ȯ�մϴ�.
	uint8_t GetLayerIndex() const;

	// 0 ~ 31 ������ ������ ���̾� �ε����� �����մϴ�.
	void SetLayerIndex(uint8_t layerIndex);

	// �����ϴ� ���̾� ��Ʈ���� ��ȯ�մϴ�.
	uint32_t GetIgnoreLayerBits() const;

	// �����Ϸ��� ���̾� ��Ʈ���� �����մϴ�.
	void SetIgnoreLayerBits(uint32_t ignoreLayers);

	// �� ���̾� �ε����� �����ϰ� �ִ����� ��ȯ�մϴ�.
	bool IsIgnore(uint8_t layerIndex);

	// �� ���̾� �ε����� �������� �����մϴ�.
	void SetIgnoreLayer(uint8_t layerIndex, bool ignore);

	__declspec(property(get = GetLayerIndex, put = SetLayerIndex)) uint8_t layerIndex;

protected:

	virtual PxGeometry* CreateGeometry() = 0;

	virtual void OnBeginPhysicsSimulate() = 0;

	virtual void UpdateScale(const Vec3& scale) = 0;

private:

	PxMaterial* CreateMaterial();

	PxShape* CreateShape(PxGeometry* geometry, PxMaterial* material);

	void ApplyCompatibleFlags();

	void ApplyLayer();

	void FindRigidbodyInTreeAndAttach();

protected:

	PxShape* m_shape = nullptr;

	PxMaterial* m_material = nullptr;

	bool m_isTrigger = false;

	uint8_t m_layerIndex = 0;

	uint32_t m_ignoreLayerBits = 0x00000000;
};

