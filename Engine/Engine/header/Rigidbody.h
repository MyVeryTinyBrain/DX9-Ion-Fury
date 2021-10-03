#pragma once

#include "Component.h"

class Rigidbody : public Component
{
	friend class Collider;

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(BeginPhysicsSimulate);

	OverrideComponentFunction(EndPhysicsSimulate);

	OverrideComponentFunction(OnDestroy);

public:

	bool UseGravity() const;

	void SetUseGravity(bool value);

	bool IsKinematic() const;

	void SetKinematic(bool value);

	bool IsContinousDetection() const;

	void SetContinuousDetection(bool value);

	void UpdateMassAndInertia();

	__declspec(property(get = UseGravity, put = SetUseGravity)) bool useGravity;

	__declspec(property(get = IsKinematic, put = SetKinematic)) bool isKinematic;

	__declspec(property(get = IsContinousDetection, put = SetContinuousDetection)) bool isContinousDetection;

public:

	void ApplyBodyTransformFromGameObject();

	void ApplyGameObjectTransfromFromBody();

	void SetPosition(const Vec3& position);

	void SetRotation(const Quat& rotation);

	void SetEulerAngle(const Vec3& eulerAngle);

	void SetLocalPosition(const Vec3& localPosition);

	void SetLocalRotation(const Quat& localRotation);

	void SetLocalEulerAngle(const Vec3& localEulerAngle);

public:

	float GetMass() const;

	void SetMass(float value);

	Vec3 GetVelocity() const;

	void SetVelocity(const Vec3& velocity);

	Vec3 GetAngularVelocity() const;

	void SetAngularVelocity(const Vec3& angularVelocity);

	void SetRotationLockAxis(Axis axes, bool value);

	bool GetRotationLockAxis(Axis axes) const;

	void SetTranslationLockAxis(Axis axes, bool value);

	bool GetTranslationLockAxis(Axis axes) const;

	__declspec(property(get = GetMass, put = SetMass)) float mass;

	__declspec(property(get = GetVelocity, put = SetVelocity)) Vec3 velocity;

	__declspec(property(get = GetAngularVelocity, put = SetAngularVelocity)) Vec3 angularVelocity;

private:

	void Attach(class Collider* collider);

	void Detach(class Collider* collider);

	void AttachAll();

	void DetachAll();

	void ApplyFlags();

private:

	PxRigidDynamic* m_body;

	bool m_continous = false;
};

