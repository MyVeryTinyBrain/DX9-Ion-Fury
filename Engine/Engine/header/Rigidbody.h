#pragma once

#include "Component.h"

class Rigidbody : public Component
{
	friend class Collider;

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(BeginPhysicsSimulate);

	OverrideComponentFunction(EndPhysicsSimulate);

	OverrideComponentFunction(OnWake);

	OverrideComponentFunction(OnSleep);

	OverrideComponentFunction(OnDestroy);

public:

	bool GetUseGravity() const;

	void SetUseGravity(bool value);

	bool IsKinematic() const;

	void SetKinematic(bool value);

	bool IsFrozenRotate(Axis axis) const;

	void SetFreezeRotate(Axis axis, bool freeze);

	bool IsFrozenTranslate(Axis axis) const;

	void SetFreezeTranslate(Axis axis, bool freeze);

public:

	float GetMass() const;

	void SetMass(float value);

	float GetLinearDamping() const;

	void SetLinearDamping(float value);

	float GetAngularDamping() const;

	void SetAngularDamping(float value);

	Vec3 GetLinearVelocity() const;

	void SetLinearVelocity(const Vec3& value);

	Vec3 GetAngularVelocity() const;

	void SetAngularVelocity(const Vec3& value);

	void SetSleep(bool value);

private:

	void SetupBody();

	void ToBody();

	void FromBody();

	void Attach(class Collider* collider);

	void Detach(class Collider* collider);

	void AttachAllColliders();

	void DetachAllColliders();

private:

	PxRigidDynamic* m_body;
};

