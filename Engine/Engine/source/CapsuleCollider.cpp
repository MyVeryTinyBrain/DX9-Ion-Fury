#include "EngineBase.h"
#include "CapsuleCollider.h"
#include "Transform.h"

PxGeometryHolder CapsuleCollider::CreateGeometry()
{
    m_defaultRotation = Quat::FromEuler(0, 0, 90);

    return CreateCapsuleGeometry();
}

float CapsuleCollider::GetRadius() const
{
    return m_radius;
}

void CapsuleCollider::SetRadius(float value)
{
    m_radius = value;
    ResetShape();
}

float CapsuleCollider::GetHalfHeight() const
{
    return m_halfHeight;
}

void CapsuleCollider::SetHalfHeight(float value)
{
    m_halfHeight = value;
    ResetShape();
}

PxCapsuleGeometry CapsuleCollider::CreateCapsuleGeometry() const
{
    PxCapsuleGeometry capsule;
    capsule.radius = m_radius * GetBiggestLengthFromAbsVec3XZ(transform->scale);
    capsule.halfHeight = m_halfHeight * Abs(transform->scale.y);
    return capsule;
}

float CapsuleCollider::GetBiggestLengthFromAbsVec3XZ(const Vec3& value) const
{
    float max = Abs(value.x);
    max = Max(max, Abs(value.z));
    return max;
}
