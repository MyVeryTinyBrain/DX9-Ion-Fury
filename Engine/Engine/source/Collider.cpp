#include "EngineBase.h"
#include "Collider.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "Transform.h"
#include "GameObject.h"
#include "LayerManager.h"

void Collider::Awake()
{
	PxGeometry* geometry = CreateGeometry();

	m_material = CreateMaterial();

	m_shape = CreateShape(geometry, m_material);

	ApplyCompatibleFlags();

	ApplyLayer();

	ApplyTransform();

	SafeDelete(geometry);
}

void Collider::Start()
{
	ApplyTransform();
}

void Collider::BeginPhysicsSimulate()
{
	ApplyTransform();

	OnBeginPhysicsSimulate();
}

void Collider::OnWake()
{
	if (!m_shape)
		return;

	ApplyCompatibleFlags();
}

void Collider::OnSleep()
{
	if (!m_shape)
		return;

	ApplyCompatibleFlags();
}

void Collider::OnDestroy()
{
	PxRelease(m_material);
	PxRelease(m_shape);
}

bool Collider::IsTrigger() const
{
	return m_isTrigger;
}

void Collider::SetTrigger(bool value)
{
	m_isTrigger = value;
	ApplyCompatibleFlags();
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

void Collider::ApplyTransform()
{
	PxTransform pose;
	pose.p = ToPxVec3(transform->localPosition);
	pose.q = ToPxQuat(transform->localRotation);

	m_shape->setLocalPose(pose);
}

void Collider::ApplyScale()
{
	UpdateScale(transform->scale);
}

void Collider::SetPosition(const Vec3& position)
{
	transform->position = position;
	ApplyTransform();
}

void Collider::SetLocalPosition(const Vec3& localPosition)
{
	transform->localPosition = localPosition;
	ApplyTransform();
}

void Collider::SetRotation(const Quat& rotation)
{
	transform->rotation = rotation;
	ApplyTransform();
}

void Collider::SetLocalRotation(const Quat& localRotation)
{
	transform->localRotation = localRotation;
	ApplyTransform();
}

void Collider::SetEulerAngle(const Vec3& eulerAngle)
{
	transform->eulerAngle = eulerAngle;
	ApplyTransform();
}

void Collider::SetLocalEulerAngle(const Vec3& localEulerAngle)
{
	transform->localEulerAngle = localEulerAngle;
	ApplyTransform();
}

void Collider::SetScale(const Vec3& scale)
{
	transform->scale = scale;
	ApplyScale();
}

void Collider::SetLocalScale(const Vec3& localScale)
{
	transform->localScale = localScale;
	ApplyScale();
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

PxMaterial* Collider::CreateMaterial()
{
	auto device = PhysicsDevice::GetInstance();

	// 생성과 동시에 참조 카운터는 1로 설정됩니다.
	return device->physics->createMaterial(0.5f, 0.5f, 0.5f);
}

PxShape* Collider::CreateShape(PxGeometry* geometry, PxMaterial* material)
{
	auto device = PhysicsDevice::GetInstance();

	// eSCENE_QUERY_SHAPE: 쿼리 관련 함수 호출을 위해서 필요한 플래그입니다.
	// 생성과 동시에 참조 카운터는 1로 설정됩니다.
	PxShape* shape = device->physics->createShape(
		*geometry, *material, true,
		PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eSIMULATION_SHAPE
	);

	// 유저 커스텀 데이터에 이 컴포넌트를 저장합니다.
	// PxShape <--> Collider 형태의 참조가 가능해집니다.
	shape->userData = this;

	return shape;
}

void Collider::ApplyCompatibleFlags()
{
	// 트리거 플래그: 트리거 모드이고 컴포넌트가 활성화 되어있으면 켜집니다.
	// 시뮬레이션 플래그: 트리거 플래그가 꺼져 있어야 하며 컴포넌트가 활성화 되어있으면 켜집니다.
	// 쿼리 플래그: 언제나 켜져 있습니다.

	bool triggerFlag = isTrigger && isWake;
	bool simulationFlag = !triggerFlag && isWake;
	bool queryFlag = true;

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

	uint32_t collisionBits = layerManager->GetCollisionBits(m_layerIndex);
	uint32_t resultBits = collisionBits & (!m_ignoreLayerBits);

	PxFilterData filter{};
	filter.word0 = (1 << m_layerIndex);
	filter.word1 = resultBits;

	m_shape->setSimulationFilterData(filter);
}
