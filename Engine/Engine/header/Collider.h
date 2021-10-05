#pragma once

#include "Component.h"
#include "PhysicsCallbackTypes.h"

/*
	PxFilterData.word0: 콜라이더에 설정된 레이어 인덱스의 비트 하나가 있습니다.
	PxFilterData.word1: 무시하지 않을 레이어 인덱스의 비트들이 있습니다.
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

	// 트리거 모드 상태를 반환합니다.
	bool IsTrigger() const;

	// 트리거 모드를 설정합니다.
	void SetTrigger(bool value);

	// 마찰을 반환합니다.
	float GetFriction() const;

	// 마찰을 설정합니다.
	void SetFriction(float value);

	// 반발력을 반환합니다.
	float GetRestitution() const;

	// 반발력을 설정합니다.
	void SetRestitution(float value);

	// 마찰 결합 모드를 반환합니다.
	PhysicsCombineMode GetFrictionCombineMode() const;

	// 마찰 결합 모드를 설정합니다.
	void SetFrictionCombineMode(PhysicsCombineMode value);

	// 강한 마찰 모드 상태를 반환합니다.
	bool IsStringFrictionMode() const;

	// 강한 마찰 상태를 설정합니다.
	void SetStringFrictionMode(bool value);

	// 콜라이더가 부착된 강체를 반환합니다.
	class Rigidbody* GetRigidbody() const;

	__declspec(property(get = IsTrigger, put = SetTrigger)) bool isTrigger;

	__declspec(property(get = GetFriction, put = SetFriction)) float friction;

	__declspec(property(get = GetRestitution, put = SetRestitution)) float restitution;

	__declspec(property(get = GetFrictionCombineMode, put = SetFrictionCombineMode)) PhysicsCombineMode frictionCombineMode;

	__declspec(property(get = IsStringFrictionMode, put = SetStringFrictionMode)) bool isStringFrictionMode;

	__declspec(property(get = GetRigidbody)) class Rigidbody* rigidbody;

public:

	// 0 ~ 31 사이의 레이어 인덱스를 반환합니다.
	uint8_t GetLayerIndex() const;

	// 0 ~ 31 사이의 값으로 레이어 인덱스를 설정합니다.
	void SetLayerIndex(uint8_t layerIndex);

	// 무시하는 레이어 비트들을 반환합니다.
	uint32_t GetIgnoreLayerBits() const;

	// 무시하려는 레이어 비트들을 설정합니다.
	void SetIgnoreLayerBits(uint32_t ignoreLayers);

	// 이 레이어 인덱스를 무시하고 있는지를 반환합니다.
	bool IsIgnore(uint8_t layerIndex);

	// 이 레이어 인덱스를 무시할지 설정합니다.
	void SetIgnoreLayer(uint8_t layerIndex, bool ignore);

	__declspec(property(get = GetLayerIndex, put = SetLayerIndex)) uint8_t layerIndex;

public:

	PxGeometryHolder GetGeometry() const;

	__declspec(property(get = GetGeometry)) PxGeometryHolder geometry;

public:

	// 변경된 위치와 회전을 콜라이더에 즉시 적용합니다.
	void ApplyTransform(bool unconditionally = false);

	// 변경된 스케일을 콜라이더에 즉시 적용합니다.
	void ApplyScale(bool unconditionally = false);

	// 콜라이더 플래그를 즉시 재설정합니다.
	void ApplyFlags();

	// 콜라이더의 레이어를 즉시 재설정합니다.
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

