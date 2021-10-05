#pragma once

#include "Component.h"
#include "PhysicsCallbackTypes.h"

/*
	PxFilterData.word0: �ݶ��̴��� ������ ���̾� �ε����� ��Ʈ �ϳ��� �ֽ��ϴ�.
	PxFilterData.word1: �������� ���� ���̾� �ε����� ��Ʈ���� �ֽ��ϴ�.
*/

enum class PhysicsCombineMode
{
	Average = PxCombineMode::eAVERAGE,
	Min = PxCombineMode::eMIN,
	Multiply = PxCombineMode::eMULTIPLY,
	Max = PxCombineMode::eMAX,
};

class Collider abstract : public Component
{
	friend class Rigidbody;

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(BeginPhysicsSimulate);

	OverrideComponentFunction(OnWake);

	OverrideComponentFunction(OnSleep);

	OverrideComponentFunction(OnDestroy);

public:

	// Ʈ���� ��� ���¸� ��ȯ�մϴ�.
	bool IsTrigger() const;

	// Ʈ���� ��带 �����մϴ�.
	void SetTrigger(bool value);

	// ������ ��ȯ�մϴ�.
	float GetFriction() const;

	// ������ �����մϴ�.
	void SetFriction(float value);

	// �ݹ߷��� ��ȯ�մϴ�.
	float GetRestitution() const;

	// �ݹ߷��� �����մϴ�.
	void SetRestitution(float value);

	// ���� ���� ��带 ��ȯ�մϴ�.
	PhysicsCombineMode GetFrictionCombineMode() const;

	// ���� ���� ��带 �����մϴ�.
	void SetFrictionCombineMode(PhysicsCombineMode value);

	// ���� ���� ��� ���¸� ��ȯ�մϴ�.
	bool IsStringFrictionMode() const;

	// ���� ���� ���¸� �����մϴ�.
	void SetStringFrictionMode(bool value);

	// �ݶ��̴��� ������ ��ü�� ��ȯ�մϴ�.
	class Rigidbody* GetRigidbody() const;

	__declspec(property(get = IsTrigger, put = SetTrigger)) bool isTrigger;

	__declspec(property(get = GetFriction, put = SetFriction)) float friction;

	__declspec(property(get = GetRestitution, put = SetRestitution)) float restitution;

	__declspec(property(get = GetFrictionCombineMode, put = SetFrictionCombineMode)) PhysicsCombineMode frictionCombineMode;

	__declspec(property(get = IsStringFrictionMode, put = SetStringFrictionMode)) bool isStringFrictionMode;

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

public:

	PxGeometryHolder GetGeometry() const;

	__declspec(property(get = GetGeometry)) PxGeometryHolder geometry;

public:

	// ����� ��ġ�� ȸ���� �ݶ��̴��� ��� �����մϴ�.
	void ApplyTransform(bool unconditionally = false);

	// ����� �������� �ݶ��̴��� ��� �����մϴ�.
	void ApplyScale(bool unconditionally = false);

	// �ݶ��̴� �÷��׸� ��� �缳���մϴ�.
	void ApplyFlags();

	// �ݶ��̴��� ���̾ ��� �缳���մϴ�.
	void ApplyLayer();

protected:

	virtual PxGeometryHolder CreateGeometry() = 0;

	void ResetShape();

public:

	void FindRigidbodyAndAttach();

protected:

	PxMaterial* m_material = nullptr;

	PxShape* m_shape = nullptr;

	Vec3 m_beforeLocalPosition = Vec3::zero();

	Quat m_beforeLocalRotation = Quat::Identity();

	Vec3 m_beforeWorldScale = Vec3::zero();

	bool m_isTrigger = false;

	uint8_t m_layerIndex = 0;

	uint32_t m_ignoreLayerBits = 0x00000000;

	Quat m_defaultRotation = Quat::Identity();

public:

	Delegate<void(const CollisionEnter&)> OnCollisionEnter;

	Delegate<void(const CollisionExit&)> OnCollisionExit;

	Delegate<void(const CollisionStay&)> OnCollisionStay;
};

