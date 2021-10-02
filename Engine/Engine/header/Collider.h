#pragma once

#include "Component.h"

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

	// �ݶ��̴��� ������ ��ü�� ��ȯ�մϴ�.
	class Rigidbody* GetRigidbody() const;

	__declspec(property(get = IsTrigger, put = SetTrigger)) bool isTrigger;

	__declspec(property(get = GetFriction, put = SetFriction)) float friction;

	__declspec(property(get = GetRestitution, put = SetRestitution)) float restitution;

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

private:

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
};

