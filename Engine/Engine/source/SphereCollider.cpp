#include "EngineBase.h"
#include "SphereCollider.h"
#include "Transform.h"

float SphereCollider::GetRadius() const
{
	return m_radius;
}

void SphereCollider::SetRadius(float value)
{
	m_radius = Abs(value);
}

PxGeometry* SphereCollider::CreateGeometry()
{
	return new PxSphereGeometry(m_radius);
}

void SphereCollider::OnBeginPhysicsSimulate()
{
	UpdateScale(transform->scale);
}

void SphereCollider::UpdateScale(const Vec3& scale)
{
	PxSphereGeometry sphere;
	m_shape->getSphereGeometry(sphere);

	sphere.radius = m_radius * GetBiggestAbsVec3(scale);

	m_shape->setGeometry(sphere);
}

float SphereCollider::GetBiggestAbsVec3(const Vec3& value) const
{
	float max = Abs(value.x);
	max = Max(max, Abs(value.y));
	max = Max(max, Abs(value.z));
	return max;
}
