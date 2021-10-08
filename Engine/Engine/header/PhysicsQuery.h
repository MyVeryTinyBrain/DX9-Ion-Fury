#pragma once

#include "PhysicsQueryTypes.h"

class Collider;

class PhysicsQuery
{
public:

    // 빠른 레이캐스트입니다.
    // 충돌 정보를 반환하지 않습니다.
    static bool RaycastTest(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 충돌 정보를 반환하는 레이캐스트입니다.
    static bool Raycast(RaycastHit& hit, const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 광선에 닿는 모든 충돌 정보를 반환하는 레이캐스트입니다.
    static std::vector<RaycastHit> RaycastAll(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);
    
    // 빠른 점 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    static bool OverlapPointTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    static Collider* OverlapPoint(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 점에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    static std::vector<Collider*> OverlapPointAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    // 빠른 지오메트리 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    static bool OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    static Collider* OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

    // 지오메트리에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    static std::vector<Collider*> OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Collider* ignoreCollider = nullptr);

    // 빠른 콜라이더 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    static bool OverlapColliderTest(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    static Collider* OverlapCollider(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 콜라이더에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    static std::vector<Collider*> OverlapColliderAll(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    static bool OverlapSphereTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

    static Collider* OverlapSphere(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

    static std::vector<Collider*> OverlapSphereAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

    static bool OverlapBoxTest(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

    static Collider* OverlapBox(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

    static std::vector<Collider*> OverlapBoxAll(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Collider* ignoreCollider = nullptr);

private:

    const static PxHitFlags bufferFlags;

    const static PxQueryFilterData defaultFilterData;

    const static PxQueryFilterData fastFilterData;
};

