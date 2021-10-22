#include "EngineBase.h"
#include "Collider.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "Transform.h"
#include "GameObject.h"
#include "LayerManager.h"
#include "Rigidbody.h"

Collider::~Collider()
{
	PxRelease(m_material);
	PxRelease(m_shape);
}

void Collider::Awake()
{
	auto device = PhysicsDevice::GetInstance();
	
	m_material = device->physics->createMaterial(1.0f, 1.0f, 0.0f);
	m_material->setFrictionCombineMode(PxCombineMode::eMIN);
	m_material->setFlag(PxMaterialFlag::eDISABLE_FRICTION, false);
	m_material->setFlag(PxMaterialFlag::eDISABLE_STRONG_FRICTION, false);
	//->setFlag(PxMaterialFlag::eIMPROVED_PATCH_FRICTION, false);

	m_shape = device->physics->createShape(CreateGeometry().any(), *m_material, true);
	m_shape->userData = this;
	
	FindRigidbodyAndAttach();

	ApplyFlags();

	ApplyTransform(true);

	ApplyScale();

	ApplyLayer();

	SetFrictionCombineMode(PhysicsCombineMode::Min);
	SetRestitutionCombineMode(PhysicsCombineMode::Min);
}

void Collider::BeginPhysicsSimulate()
{
	ApplyTransform();
	ApplyScale();
}

void Collider::OnWake()
{
	if (!m_shape)
		return;

	ApplyFlags();

	if (rigidbody)
	{
		rigidbody->SetRigidbodySleep(false);
	}
}

void Collider::OnSleep()
{
	if (!m_shape)
		return;

	ApplyFlags();
}

void Collider::OnDestroy()
{
	Rigidbody* body = GetRigidbody();
	if (body)
		body->Detach(this);
}

bool Collider::IsTrigger() const
{
	return m_isTrigger;
}

void Collider::SetTrigger(bool value)
{
	m_isTrigger = value;
	ApplyFlags();
}

float Collider::GetFriction() const
{
	return m_material->getDynamicFriction();
}

void Collider::SetFriction(float value)
{
	m_material->setStaticFriction(value);
	m_material->setDynamicFriction(value);
}

float Collider::GetRestitution() const
{
	return m_material->getRestitution();
}

void Collider::SetRestitution(float value)
{
	return m_material->setRestitution(value);
}

PhysicsCombineMode Collider::GetFrictionCombineMode() const
{
	return (PhysicsCombineMode)m_material->getFrictionCombineMode();
}

void Collider::SetFrictionCombineMode(PhysicsCombineMode value)
{
	m_material->setFrictionCombineMode((PxCombineMode::Enum)value);
}

PhysicsCombineMode Collider::GetRestitutionCombineMode() const
{
	return (PhysicsCombineMode)m_material->getRestitutionCombineMode();
}

void Collider::SetRestitutionCombineMode(PhysicsCombineMode value)
{
	m_material->setRestitutionCombineMode((PxCombineMode::Enum)value);
}

bool Collider::IsStringFrictionMode() const
{
	return !m_material->getFlags().isSet(PxMaterialFlag::eDISABLE_STRONG_FRICTION);
}

void Collider::SetStringFrictionMode(bool value)
{
	m_material->setFlag(PxMaterialFlag::eDISABLE_STRONG_FRICTION, !value);
}

Rigidbody* Collider::GetRigidbody() const
{
	PxRigidActor* actor = m_shape->getActor();
	if (!actor)
		return nullptr;
	return (Rigidbody*)actor->userData;
}

uint8_t Collider::GetLayerIndex() const
{
	return m_layerIndex;
}

void Collider::SetLayerIndex(uint8_t layerIndex)
{
	assert(layerIndex < PhysicsLayerMax);

	m_layerIndex = layerIndex;

	ApplyLayer();
}

uint32_t Collider::GetIgnoreLayerBits() const
{
	return m_ignoreLayerBits;
}

void Collider::SetIgnoreLayerBits(uint32_t ignoreLayers)
{
	m_ignoreLayerBits = ignoreLayers;

	ApplyLayer();
}

bool Collider::IsIgnore(uint8_t layerIndex)
{
	assert(layerIndex < PhysicsLayerMax);

	return m_ignoreLayerBits & (1 << layerIndex);
}

void Collider::SetIgnoreLayer(uint8_t layerIndex, bool ignore)
{
	assert(layerIndex < PhysicsLayerMax);

	if (ignore)
	{
		m_ignoreLayerBits |= (1 << layerIndex);
	}
	else
	{
		m_ignoreLayerBits &= !(1 << layerIndex);
	}

	ApplyLayer();
}

PxGeometryHolder Collider::GetGeometry() const
{
	return m_shape->getGeometry();
}

void Collider::ApplyTransform(bool unconditionally)
{
	Vec3 localPositionFromBody;
	Quat localRotationFromBody;

	if (rigidbody)
	{
		localPositionFromBody = rigidbody->transform->worldToLocal.MultiplyPoint(transform->position);
		localRotationFromBody = rigidbody->transform->rotation.inversed() * transform->rotation;
	}
	else
	{
		localPositionFromBody = Vec3::zero();
		localRotationFromBody = Quat::Identity();
	}
	
	if (unconditionally ||
		Vec3::Distance(localPositionFromBody, m_beforeLocalPosition) > 0.01f ||
		Quat::Radian(localRotationFromBody, m_beforeLocalRotation) > 0.01f)
	{
		float e = 0.01f;
		float a = Vec3::Distance(localPositionFromBody, m_beforeLocalPosition);
		float b = Quat::Radian(localRotationFromBody, m_beforeLocalRotation);

		bool fa = a > e;
		bool fb = b > e;

		m_beforeLocalPosition = localPositionFromBody;
		m_beforeLocalRotation = localRotationFromBody;

		PxTransform pose;
		pose.p = ToPxVec3(localPositionFromBody);
		pose.q = ToPxQuat(localRotationFromBody) * ToPxQuat(m_defaultRotation);
		m_shape->setLocalPose(pose);
	}
}

void Collider::ApplyScale(bool unconditionally)
{
	Vec3 worldScale;

	worldScale = transform->scale;

	if (unconditionally || 
		worldScale != m_beforeWorldScale)
	{
		m_beforeWorldScale = worldScale;

		ResetShape();
	}
}

void Collider::ApplyFlags()
{
	// Ʈ���� �÷���: Ʈ���� ����̰� ������Ʈ�� Ȱ��ȭ �Ǿ������� �����ϴ�.
	// �ùķ��̼� �÷���: Ʈ���� �÷��װ� ���� �־�� �ϸ� ������Ʈ�� Ȱ��ȭ �Ǿ������� �����ϴ�.
	// ���� �÷���: ������Ʈ�� Ȱ��ȭ ���¶�� ������ ���� �ֽ��ϴ�.

	bool triggerFlag = isTrigger && isWake;
	bool simulationFlag = !triggerFlag && isWake;
	bool queryFlag = isWake;

	// eTRIGGER_SHAPE �÷��׸� Ȱ��ȭ �ϱ� ������ �ݵ�� eSIMULATION_SHAPE �÷��װ� ��Ȱ��ȭ ���¿��� �մϴ�.
	// ������ �Ʒ��� ���� ������ �÷��׸� �����մϴ�.

	m_shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, simulationFlag);
	m_shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, triggerFlag);
	m_shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, queryFlag);
}

void Collider::ApplyLayer()
{
	auto device = PhysicsDevice::GetInstance();
	auto layerManager = device->layerManager;

	// ������ ���̾ ������ ��� ��Ʈ�� �մϴ�.
	uint32_t unignoreBits = ~m_ignoreLayerBits;

	PxFilterData filter{};

	// ���̾� ��Ʈ�� �մϴ�.
	filter.word0 = (1 << m_layerIndex);

	// �������� �ʴ� ��Ʈ���� �մϴ�.
	filter.word1 = unignoreBits;

	m_shape->setSimulationFilterData(filter);
}

void Collider::ResetShape()
{
	m_shape->setGeometry(CreateGeometry().any());

	Rigidbody* body = GetRigidbody();
	if (body)
	{
		body->UpdateMassAndInertia();
	}
}

void Collider::FindRigidbodyAndAttach()
{
	// ���� Ʈ������ ��ü�� ã�� �����մϴ�.

	if (rigidbody)
		return;

	Transform* t = transform;

	while (t)
	{
		auto body = t->gameObject->GetComponent<Rigidbody>();
		if (body)
		{
			body->Attach(this);
			ApplyTransform();
			return;
		}
		t = t->parent;
	}
}
