#include "EngineBase.h"
#include "SphereCollider.h"
#include "Transform.h"

PxGeometryHolder SphereCollider::CreateGeometry()
{
    return CreateSphereGeometry();
}

float SphereCollider::GetRadius() const
{
    return m_radius;
}

void SphereCollider::SetRadius(float value)
{
    m_radius = value;
    ApplyScale();
}

PxSphereGeometry SphereCollider::CreateSphereGeometry() const
{
    PxSphereGeometry sphere;
    sphere.radius = m_radius * GetBiggestLengthFromAbsVec3(transform->scale);
    return sphere;
}

float SphereCollider::GetBiggestLengthFromAbsVec3(const Vec3& value) const
{
    float max = Abs(value.x);
    max = Max(max, Abs(value.y));
    max = Max(max, Abs(value.z));
    return max;
}
