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

	bool IsKinematic() const;

	void SetKinematic(bool value);

	void UpdateMassAndInertia();

	__declspec(property(get = IsKinematic, put = SetKinematic)) bool isKinematic;

public:

	void ApplyBodyTransformFromGameObject();

	void ApplyGameObjectTransfromFromBody();

	void SetPosition(const Vec3& position);

	void SetRotation(const Quat& rotation);

	void SetVelocity(const Vec3& velocity);

	void SetRotationLockAxis(Axis axes, bool value);

	bool GetRotationLockAxis(Axis axes) const;

	void SetTranslationLockAxis(Axis axes, bool value);

	bool GetTranslationLockAxis(Axis axes) const;

private:

	void Attach(class Collider* collider);

	void Detach(class Collider* collider);

	void AttachAll();

	void DetachAll();

private:

	PxRigidDynamic* m_body;
};

