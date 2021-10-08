#pragma once

#include "PhysicsQueryTypes.h"

class Collider;
class Rigidbody;

class PhysicsQuery
{
public:

    // ���� ����ĳ��Ʈ�Դϴ�.
    // �浹 ������ ��ȯ���� �ʽ��ϴ�.
    static bool RaycastTest(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ����� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
    static bool Raycast(RaycastHit& hit, const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ������ ��� ��� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
    static std::vector<RaycastHit> RaycastAll(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);
    
    // ���� �� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    static bool OverlapPointTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    static Collider* OverlapPoint(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    static std::vector<Collider*> OverlapPointAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // ���� ������Ʈ�� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    static bool OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    static Collider* OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ������Ʈ���� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    static std::vector<Collider*> OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // ���� �ݶ��̴� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    static bool OverlapColliderTest(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    static Collider* OverlapCollider(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // �ݶ��̴��� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    static std::vector<Collider*> OverlapColliderAll(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    static bool OverlapSphereTest(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static Collider* OverlapSphere(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<Collider*> OverlapSphereAll(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    static bool OverlapBoxTest(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static Collider* OverlapBox(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<Collider*> OverlapBoxAll(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

private:

    const static PxHitFlags bufferFlags;

    const static PxQueryFilterData defaultFilterData;

    const static PxQueryFilterData fastFilterData;
};

