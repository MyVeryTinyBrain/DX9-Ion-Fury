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

	ApplyFlags();

	device->scene->addActor(*m_body);

	AttachAll();

	ApplyBodyTransformFromGameObject();
}

void Rigidbody::BeginPhysicsSimulate()
{
	ApplyBodyTransformFromGameObject();
}

void Rigidbody::EndPhysicsSimulate()
{
	ApplyGameObjectTransfromFromBody();
}

void Rigidbody::OnDestroy()
{
	DetachAll();
	PxRelease(m_body);
}

bool Rigidbody::UseGravity() const
{
	return m_body->getActorFlags().isSet(PxActorFlag::eDISABLE_GRAVITY);
}

void Rigidbody::SetUseGravity(bool value)
{
	m_body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, value);
}

bool Rigidbody::IsKinematic() const
{
	return m_body->getRigidBodyFlags().isSet(PxRigidBodyFlag::eKINEMATIC);;
}

void Rigidbody::SetKinematic(bool value)
{
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, value);
}

bool Rigidbody::IsContinousDetection() const
{
	// ����
	// Kinematic Rigidbody�� Continous Detection�� �������� �ʽ��ϴ�.
	// �� �Լ��� ��ȯ�ϴ� ���� Continous Detection�� ����Ϸ��� ��û�ϴ� �÷����Դϴ�.

	return m_continous;
}

void Rigidbody::SetContinuousDetection(bool value)
{
	m_continous = value;

	ApplyFlags();
}

void Rigidbody::UpdateMassAndInertia()
{
	PxRigidBodyExt::setMassAndUpdateInertia(*m_body, m_body->getMass());
}

void Rigidbody::ApplyBodyTransformFromGameObject()
{
	PxTransform pose = m_body->getGlobalPose();

	pose.p = ToPxVec3(transform->position);

	if (Quat::Radian(FromPxQuat(pose.q), transform->rotation) > 0.01f)
	{
		pose.q = ToPxQuat(transform->rotation);
	}

	m_body->setGlobalPose(pose);
}

void Rigidbody::ApplyGameObjectTransfromFromBody()
{
	PxTransform pose = m_body->getGlobalPose();

	transform->position = FromPxVec3(pose.p);

	transform->rotation = FromPxQuat(pose.q);
}

void Rigidbody::SetPosition(const Vec3& position)
{
	transform->position = position;
	PxTransform pose = m_body->getGlobalPose();
	pose.p = ToPxVec3(position);
	m_body->setGlobalPose(pose);
}

void Rigidbody::SetRotation(const Quat& rotation)
{
	transform->rotation = rotation;
	PxTransform pose = m_body->getGlobalPose();
	pose.q = ToPxQuat(rotation);
	m_body->setGlobalPose(pose);
}

void Rigidbody::SetEulerAngle(const Vec3& eulerAngle)
{
	transform->eulerAngle = eulerAngle;
	PxTransform pose = m_body->getGlobalPose();
	pose.q = ToPxQuat(transform->rotation);
	m_body->setGlobalPose(pose);
}

void Rigidbody::SetLocalPosition(const Vec3& localPosition)
{
	transform->localPosition = localPosition;
	PxTransform pose = m_body->getGlobalPose();
	pose.p = ToPxVec3(transform->position);
	m_body->setGlobalPose(pose);
}

void Rigidbody::SetLocalRotation(const Quat& localRotation)
{
	transform->localRotation = localRotation;
	PxTransform pose = m_body->getGlobalPose();
	pose.q = ToPxQuat(transform->rotation);
	m_body->setGlobalPose(pose);
}

void Rigidbody::SetLocalEulerAngle(const Vec3& localEulerAngle)
{
	transform->localEulerAngle = localEulerAngle;
	PxTransform pose = m_body->getGlobalPose();
	pose.q = ToPxQuat(transform->rotation);
	m_body->setGlobalPose(pose);
}

float Rigidbody::GetMass() const
{
	return m_body->getMass();
}

void Rigidbody::SetMass(float value)
{
	if (value < 0)
		value = 0;
	m_body->setMass(value);
	UpdateMassAndInertia();
}

Vec3 Rigidbody::GetVelocity() const
{
	PxVec3 pxVelocity = m_body->getLinearVelocity();
	return FromPxVec3(pxVelocity);
}

void Rigidbody::SetVelocity(const Vec3& velocity)
{
	PxVec3 pxVelocity = ToPxVec3(velocity);
	m_body->setLinearVelocity(pxVelocity);
}

Vec3 Rigidbody::GetAngularVelocity() const
{
	PxVec3 pxAVelocity = m_body->getAngularVelocity();
	return FromPxVec3(pxAVelocity);
}

void Rigidbody::SetAngularVelocity(const Vec3& angularVelocity)
{
	PxVec3 pxAngularVelocity = ToPxVec3(angularVelocity);
	m_body->setAngularVelocity(pxAngularVelocity);
}

void Rigidbody::SetRotationLockAxis(Axis axes, bool value)
{
	PxU32 flag = (PxU32)axes << 3;
	m_body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::Enum(flag), value);
}

bool Rigidbody::GetRotationLockAxis(Axis axes) const
{
	PxU32 flag = (PxU32)axes << 3;
	PxU32 flags = (PxU32)m_body->getRigidDynamicLockFlags();
	return flag & flags;
}

void Rigidbody::SetTranslationLockAxis(Axis axes, bool value)
{
	PxU32 flag = (PxU32)axes << 0;
	m_body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::Enum(flag), value);
}

bool Rigidbody::GetTranslationLockAxis(Axis axes) const
{
	PxU32 flag = (PxU32)axes << 0;
	PxU32 flags = (PxU32)m_body->getRigidDynamicLockFlags();
	return flag & flags;
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

void Rigidbody::ApplyFlags()
{
	// ���� �浹 ���� ��带 �����մϴ�.
	bool continousFlag = m_continous && !IsKinematic();
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, continousFlag);

	// ���� �浹 ��� ���� ������ ����մϴ�.
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD_FRICTION, continousFlag);

	// A -- B ���� �浹 �˸��� ���� �����մϴ�.
	// eFORCE_KINE_KINE_NOTIFICATIONS
	// eFORCE_STATIC_KINE_NOTIFICATIONS 
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eFORCE_KINE_KINE_NOTIFICATIONS, true);
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eFORCE_STATIC_KINE_NOTIFICATIONS, true);

	// �ùķ��̼� �߿� Kinemtic Rigidbody�� �����Ҽ� �ְ� �˴ϴ�.
	// �� �����ӿ�ũ�� �ùķ��̼��� ���� �Ŀ� �����ϰ� �˴ϴ�.
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, true);

	// �ùķ��̼ǿ� ���� Pose ��ȭ�� �����մϴ�.
	// PxSimulationEventCallback::onAdvance() �Լ��� ȣ���մϴ�.
	// m_body->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_POSE_INTEGRATION_PREVIEW, true);
}
