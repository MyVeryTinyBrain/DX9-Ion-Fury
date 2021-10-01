#include "EngineBase.h"
#include "BoxCollider.h"
#include "PhysicsDefines.h"
#include "Transform.h"

const Vec3& BoxCollider::GetExtents() const
{
	return m_extents;
}

void BoxCollider::SetExtents(const Vec3& value)
{
	m_extents = Vec3(Abs(value.x), Abs(value.y), Abs(value.z));
}

PxGeometry* BoxCollider::CreateGeometry()
{
	return new PxBoxGeometry(ToPxVec3(m_extents * 0.5f));
}

void BoxCollider::OnBeginPhysicsSimulate()
{
	UpdateScale(transform->scale);
}

void BoxCollider::UpdateScale(const Vec3& scale)
{
	PxBoxGeometry box;
	m_shape->getBoxGeometry(box);

	box.halfExtents = PxVec3(
		Abs(m_extents.x * scale.x),
		Abs(m_extents.y * scale.y),
		Abs(m_extents.z * scale.z)
	) * 0.5f;

	m_shape->setGeometry(box);
}
