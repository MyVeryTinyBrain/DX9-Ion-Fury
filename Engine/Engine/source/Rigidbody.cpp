#include "EngineBase.h"
#include "Rigidbody.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "Transform.h"
#include "Collider.h"
#include "GameObject.h"

void Rigidbody::Awake()
{
	auto device = PhysicsDevice::GetInstance();

	PxTransform initPose(PxIdentity);
	m_body = device->physics->createRigidDynamic(initPose);
	m_body->setMass(1);
	m_body->userData = this;

	device->scene->addActor(*m_body);

	AttachAll();
}

void Rigidbody::EndPhysicsSimulate()
{
	PxTransform pose = m_body->getGlobalPose();
	
	transform->position = FromPxVec3(pose.p);
	transform->rotation = FromPxQuat(pose.q);
}

void Rigidbody::OnDestroy()
{
	DetachAll();
	PxRelease(m_body);
}

bool Rigidbody::IsKinematic() const
{
	return m_body->getRigidBodyFlags().isSet(PxRigidBodyFlag::eKINEMATIC);;
}

void Rigidbody::SetKinematic(bool value)
{
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, value);
}

void Rigidbody::UpdateMassAndInertia()
{
	PxRigidBodyExt::setMassAndUpdateInertia(*m_body, m_body->getMass());
}

void Rigidbody::SetPosition(const Vec3& position)
{
	PxTransform pose = m_body->getGlobalPose();
	pose.p = ToPxVec3(position);
	m_body->setGlobalPose(pose);
}

void Rigidbody::SetVelocity(const Vec3& velocity)
{
	PxVec3 pxVelocity = ToPxVec3(velocity);
	m_body->setLinearVelocity(pxVelocity);
}

void Rigidbody::Attach(Collider* collider)
{
	if (!collider->m_shape)
		return;

	m_body->attachShape(*(collider->m_shape));
	UpdateMassAndInertia();
}

void Rigidbody::Detach(Collider* collider)
{
	if (!collider->m_shape)
		return;

	m_body->detachShape(*(collider->m_shape));
	UpdateMassAndInertia();
}

void Rigidbody::AttachAll()
{
	DetachAll();

	std::vector<Collider*> colliders = gameObject->GetComponentsInChild<Collider>();
	for (auto collider : colliders)
	{
		Attach(collider);
	}
}

void Rigidbody::DetachAll()
{
	PxU32 nb = m_body->getNbShapes();
	PxShape** shapes = new PxShape * [nb];
	m_body->getShapes(shapes, sizeof(PxShape*) * nb);

	for (PxU32 i = 0; i < nb; ++i)
	{
		m_body->detachShape(*shapes[i]);
	}

	SafeDeleteArray(shapes);
}
