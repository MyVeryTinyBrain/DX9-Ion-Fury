#include "EngineBase.h"
#include "BoxCollider.h"
#include "PhysicsDefines.h"
#include "Transform.h"

PxGeometryHolder BoxCollider::CreateGeometry()
{
	return CreateBoxGeometry();
}

void BoxCollider::SetExtents(const Vec3& extents)
{
	m_extents = extents;
	ResetShape();
}

const Vec3& BoxCollider::GetExtents() const
{
	return m_extents;
}

PxBoxGeometry BoxCollider::CreateBoxGeometry() const
{
	Vec3 extentsWithScale = Vec3(
		m_extents.x * transform->scale.x,
		m_extents.y * transform->scale.y,
		m_extents.z * transform->scale.z
	);

	PxBoxGeometry box;
	box.halfExtents = ToPxVec3(extentsWithScale) * 0.5f;
	return box;
}
