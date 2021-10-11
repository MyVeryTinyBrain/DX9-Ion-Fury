#include "EngineBase.h"
#include "CapsuleCollider.h"
#include "Transform.h"

PxGeometryHolder CapsuleCollider::CreateGeometry()
{
    // PhysX의 캡슐은 기본적으로 누워 있습니다.
    // z축에서 90도 회전하면 서 있는 캡슐이 됩니다.
    // 여기서는 서 있는 캡슐을 기본으로 사용하겠습니다.
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
