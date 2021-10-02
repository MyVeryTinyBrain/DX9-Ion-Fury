#include "EngineBase.h"
#include "Rigidbody.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "Transform.h"
#include "Collider.h"
#include "GameObject.h"

void Rigidbody::Awake()
{
	SetupBody();
}

void Rigidbody::BeginPhysicsSimulate()
{
	ToBody();
}

void Rigidbody::EndPhysicsSimulate()
{
	FromBody();
}

void Rigidbody::OnWake()
{
	m_body->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
}

void Rigidbody::OnSleep()
{
	m_body->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
}

void Rigidbody::OnDestroy()
{
	DetachAllColliders();

	PxRelease(m_body);
}

bool Rigidbody::GetUseGravity() const
{
	return !m_body->getActorFlags().isSet(PxActorFlag::eDISABLE_GRAVITY);
}

void Rigidbody::SetUseGravity(bool value)
{
	m_body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !value);
}

bool Rigidbody::IsKinematic() const
{
	return m_body->getRigidBodyFlags() & PxRigidBodyFlag::eKINEMATIC;
}

void Rigidbody::SetKinematic(bool value)
{
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, value);
}

bool Rigidbody::IsFrozenRotate(Axis axis) const
{
	unsigned int uiAxis = unsigned int(axis) + 3;
	PxRigidDynamicLockFlag::Enum lockFlag = PxRigidDynamicLockFlag::Enum(1 << uiAxis);
	return m_body->getRigidDynamicLockFlags().isSet(lockFlag);
}

void Rigidbody::SetFreezeRotate(Axis axis, bool freeze)
{
	unsigned int uiAxis = unsigned int(axis) + 3;
	PxRigidDynamicLockFlag::Enum lockFlag = PxRigidDynamicLockFlag::Enum(1 << uiAxis);
	m_body->setRigidDynamicLockFlag(lockFlag, freeze);
}

bool Rigidbody::IsFrozenTranslate(Axis axis) const
{
	unsigned int uiAxis = unsigned int(axis);
	PxRigidDynamicLockFlag::Enum lockFlag = PxRigidDynamicLockFlag::Enum(1 << uiAxis);
	return m_body->getRigidDynamicLockFlags().isSet(lockFlag);
}

void Rigidbody::SetFreezeTranslate(Axis axis, bool freeze)
{
	unsigned int uiAxis = unsigned int(axis);
	PxRigidDynamicLockFlag::Enum lockFlag = PxRigidDynamicLockFlag::Enum(1 << uiAxis);
	m_body->setRigidDynamicLockFlag(lockFlag, freeze);
}

float Rigidbody::GetMass() const
{
	return m_body->getMass();
}

void Rigidbody::SetMass(float value)
{
	m_body->setMass(value);
}

float Rigidbody::GetLinearDamping() const
{
	return m_body->getLinearDamping();
}

void Rigidbody::SetLinearDamping(float value)
{
	m_body->setLinearDamping(value);
}

float Rigidbody::GetAngularDamping() const
{
	return m_body->getAngularDamping();
}

void Rigidbody::SetAngularDamping(float value)
{
	m_body->setAngularDamping(value);
}

Vec3 Rigidbody::GetLinearVelocity() const
{
	Vec3 value = FromPxVec3(m_body->getLinearVelocity());
	return value;
}

void Rigidbody::SetLinearVelocity(const Vec3& value)
{
	PxVec3 pxValue = ToPxVec3(value);
	m_body->setLinearVelocity(pxValue);
}

Vec3 Rigidbody::GetAngularVelocity() const
{
	Vec3 value = FromPxVec3(m_body->getAngularVelocity());
	return value;
}

void Rigidbody::SetAngularVelocity(const Vec3& value)
{
	PxVec3 pxValue = ToPxVec3(value);
	m_body->setAngularVelocity(pxValue);
}

void Rigidbody::SetSleep(bool value)
{
	if (value)
		m_body->wakeUp();
	else
		m_body->putToSleep();
}

void Rigidbody::SetupBody()
{
	auto device = PhysicsDevice::GetInstance();

	PxTransform initPose;
	initPose.p = ToPxVec3(transform->position);
	initPose.q = ToPxQuat(transform->rotation);

	// 생성과 동시에 참조 카운터는 1로 설정됩니다.
	m_body = device->physics->createRigidDynamic(initPose);
	
	m_body->userData = this;

	device->scene->addActor(*m_body);
}

void Rigidbody::ToBody()
{
	PxTransform bodyPose = m_body->getGlobalPose();
	Vec3 bodyPos = FromPxVec3(bodyPose.p);
	Quat bodyRot = FromPxQuat(bodyPose.q);

	bool updatePos =
		Abs(bodyPos.x - transform->position.x) > PX_EPS_REAL ||
		Abs(bodyPos.y - transform->position.y) > PX_EPS_REAL ||
		Abs(bodyPos.z - transform->position.z) > PX_EPS_REAL;

	bool updateRot =
		Quat::Angle(bodyRot, transform->rotation) > PX_EPS_REAL;

	if (updatePos || updateRot)
	{
		if (updatePos)
		{
			bodyPose.p = ToPxVec3(transform->position);
		}
		if (updateRot)
		{
			bodyPose.q = ToPxQuat(transform->rotation);
		}
		m_body->setGlobalPose(bodyPose);
	}
}

void Rigidbody::FromBody()
{
	PxTransform bodyPose = m_body->getGlobalPose();
	Vec3 bodyPos = FromPxVec3(bodyPose.p);
	Quat bodyRot = FromPxQuat(bodyPose.q);

	bool updatePos =
		Abs(bodyPos.x - transform->position.x) > PX_EPS_REAL ||
		Abs(bodyPos.y - transform->position.y) > PX_EPS_REAL ||
		Abs(bodyPos.z - transform->position.z) > PX_EPS_REAL;

	bool updateRot =
		Quat::Angle(bodyRot, transform->rotation) > PX_EPS_REAL;

	if (updatePos)
	{
		transform->position = bodyPos;
	}
	if (updateRot)
	{
		transform->rotation = bodyRot;
	}
}

void Rigidbody::Attach(Collider* collider)
{
	m_body->attachShape(*collider->m_shape);

	PxRigidBodyExt::updateMassAndInertia(*m_body, 10);
}

void Rigidbody::Detach(Collider* collider)
{
	m_body->detachShape(*collider->m_shape);
}

void Rigidbody::AttachAllColliders()
{
	DetachAllColliders();

	std::vector<Collider*> colliders = gameObject->GetComponentsInChild<Collider>();
	for (auto collider : colliders)
	{
		Attach(collider);
	}
}

void Rigidbody::DetachAllColliders()
{
	PxU32 nbShapes = m_body->getNbShapes();

	if (nbShapes == 0)
		return;

	PxShape** shapes = new PxShape * [nbShapes];
	m_body->getShapes(shapes, sizeof(PxShape*) * nbShapes);

	for (PxU32 i = 0; i < nbShapes; ++i)
	{
		Collider* collider = (Collider*)shapes[i]->userData;
		Detach(collider);
	}

	SafeDeleteArray(shapes);
}
