#pragma once

#include "Component.h"

class Rigidbody : public Component
{
	friend class Collider;

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(EndPhysicsSimulate);

	OverrideComponentFunction(OnDestroy);

public:

	bool IsKinematic() const;

	void SetKinematic(bool value);

	void UpdateMassAndInertia();

	__declspec(property(get = IsKinematic, put = SetKinematic)) bool isKinematic;

public:

	void SetPosition(const Vec3& position);

	void SetVelocity(const Vec3& velocity);

private:

	void Attach(class Collider* collider);

	void Detach(class Collider* collider);

	void AttachAll();

	void DetachAll();

private:

	PxRigidDynamic* m_body;
};

