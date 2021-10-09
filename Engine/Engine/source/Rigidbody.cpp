#include "EngineBase.h"
#include "Rigidbody.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "Transform.h"
#include "Collider.h"
#include "GameObject.h"
#include "RigidbodyInterpolationer.h"

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

	m_interpolationer = new RigidbodyInterpolationer(this);
}

void Rigidbody::Start()
{
	m_interpolationer->BackupPose();
}

void Rigidbody::BeginPhysicsSimulate()
{
	if (m_interpolate)
	{
		m_interpolationer->RollbackPose();
	}

	ApplyBodyTransformFromGameObject();
}

void Rigidbody::EndPhysicsSimulate()
{
	ApplyGameObjectTransfromFromBody();

	if (m_interpolate)
	{
		m_interpolationer->BackupPose();
	}
}

void Rigidbody::Update()
{
	if (m_interpolate)
	{
		m_interpolationer->InterpolatePose();
	}
}

void Rigidbody::UpdateCheck()
{
	if (m_interpolate)
	{
		m_interpolationer->CheckPoseChange();
	}
}

void Rigidbody::OnDestroy()
{
	DetachAll();
	PxRelease(m_body);
	SafeDelete(m_interpolationer);
}

bool Rigidbody::UseGravity() const
{
	return !m_body->getActorFlags().isSet(PxActorFlag::eDISABLE_GRAVITY);
}

void Rigidbody::SetUseGravity(bool value)
{
	m_body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !value);
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

void Rigidbody::ApplyBodyTransformFromGameObject()
{
	PxTransform pose = m_body->getGlobalPose();

	bool hasChanged = false;

	Vec3 deltaPos = transform->position - FromPxVec3(pose.p);

	if (deltaPos.magnitude() > 0.001f)
	{
		hasChanged = true;
		pose.p = ToPxVec3(transform->position);
	}

	if (Quat::Radian(FromPxQuat(pose.q), transform->rotation) > 0.01f)
	{
		hasChanged = true;
		pose.q = ToPxQuat(transform->rotation);
	}

	if (hasChanged)
	{
		m_body->setGlobalPose(pose);
	}
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

void Rigidbody::UpdateMassAndInertia()
{
	PxRigidBodyExt::setMassAndUpdateInertia(*m_body, m_body->getMass());
}

bool Rigidbody::IsInterpolateMode() const
{
	return m_interpolate;
}

void Rigidbody::SetInterpolate(bool value)
{
	if (m_interpolate == value)
	{
		return;
	}

	m_interpolate = value;

	if (m_interpolate)
	{
		m_interpolationer->BackupPose();
	}
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

void Rigidbody::SetLinearDamping(float value)
{
	m_body->setLinearDamping(value);
}

float Rigidbody::GetLinearDamping() const
{
	return m_body->getLinearDamping();
}

void Rigidbody::SetAngularDamping(float value)
{
	m_body->setAngularDamping(value);
}

float Rigidbody::GetAngularDamping() const
{
	return m_body->getAngularDamping();
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

void Rigidbody::AddForce(const Vec3& force, ForceMode forceMode)
{
	PxVec3 pxForce = ToPxVec3(force);
	m_body->addForce(pxForce, (PxForceMode::Enum)forceMode);
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

void Rigidbody::SetRotationLockAxis(PhysicsAxis axes, bool value)
{
	PxU32 flag = (PxU32)axes << 3;
	m_body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::Enum(flag), value);
}

bool Rigidbody::GetRotationLockAxis(PhysicsAxis axes) const
{
	PxU32 flag = (PxU32)axes << 3;
	PxU32 flags = (PxU32)m_body->getRigidDynamicLockFlags();
	return flag & flags;
}

void Rigidbody::SetTranslationLockAxis(PhysicsAxis axes, bool value)
{
	PxU32 flag = (PxU32)axes << 0;
	m_body->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::Enum(flag), value);
}

bool Rigidbody::GetTranslationLockAxis(PhysicsAxis axes) const
{
	PxU32 flag = (PxU32)axes << 0;
	PxU32 flags = (PxU32)m_body->getRigidDynamicLockFlags();
	return flag & flags;
}

void Rigidbody::SetPositionIteration(uint8_t count)
{
	PxU32 pi, vi;
	m_body->getSolverIterationCounts(pi, vi);
	m_body->setSolverIterationCounts(count, vi);
}

uint8_t Rigidbody::GetPositionIteration() const
{
	PxU32 pi, vi;
	m_body->getSolverIterationCounts(pi, vi);
	return pi;
}

void Rigidbody::SetVelocityIteration(uint8_t count)
{
	PxU32 pi, vi;
	m_body->getSolverIterationCounts(pi, vi);
	m_body->setSolverIterationCounts(pi, count);
}

uint8_t Rigidbody::GetVelocityIteration() const
{
	PxU32 pi, vi;
	m_body->getSolverIterationCounts(pi, vi);
	return vi;
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
	// m_body->setRigidBodyFlag(PxRigidBodyFlag::eFORCE_KINE_KINE_NOTIFICATIONS, true);
	// m_body->setRigidBodyFlag(PxRigidBodyFlag::eFORCE_STATIC_KINE_NOTIFICATIONS, true);

	// �ùķ��̼� �߿� Kinemtic Rigidbody�� �����Ҽ� �ְ� �˴ϴ�.
	// �� �����ӿ�ũ�� �ùķ��̼��� ���� �Ŀ� �����ϰ� �˴ϴ�.
	m_body->setRigidBodyFlag(PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, true);

	// �ùķ��̼ǿ� ���� Pose ��ȭ�� �����մϴ�.
	// PxSimulationEventCallback::onAdvance() �Լ��� ȣ���մϴ�.
	// m_body->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_POSE_INTEGRATION_PREVIEW, true);
}
