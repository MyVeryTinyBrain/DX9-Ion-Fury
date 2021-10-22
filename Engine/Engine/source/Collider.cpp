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
	// 트리거 플래그: 트리거 모드이고 컴포넌트가 활성화 되어있으면 켜집니다.
	// 시뮬레이션 플래그: 트리거 플래그가 꺼져 있어야 하며 컴포넌트가 활성화 되어있으면 켜집니다.
	// 쿼리 플래그: 컴포넌트가 활성화 상태라면 언제나 켜져 있습니다.

	bool triggerFlag = isTrigger && isWake;
	bool simulationFlag = !triggerFlag && isWake;
	bool queryFlag = isWake;

	// eTRIGGER_SHAPE 플래그를 활성화 하기 전에는 반드시 eSIMULATION_SHAPE 플래그가 비활성화 상태여야 합니다.
	// 때문에 아래와 같은 순서로 플래그를 설정합니다.

	m_shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, simulationFlag);
	m_shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, triggerFlag);
	m_shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, queryFlag);
}

void Collider::ApplyLayer()
{
	auto device = PhysicsDevice::GetInstance();
	auto layerManager = device->layerManager;

	// 무시할 레이어를 제외한 모든 비트를 켭니다.
	uint32_t unignoreBits = ~m_ignoreLayerBits;

	PxFilterData filter{};

	// 레이어 비트를 켭니다.
	filter.word0 = (1 << m_layerIndex);

	// 무시하지 않는 비트들을 켭니다.
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
	// 위쪽 트리에서 강체를 찾아 부착합니다.

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
