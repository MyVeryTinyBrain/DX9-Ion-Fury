#pragma once

#include "PhysicsQueryTypes.h"

class Collider;
class Rigidbody;

class PhysicsQuery
{
public:

    // 빠른 레이캐스트입니다.
    // 충돌 정보를 반환하지 않습니다.
    static bool RaycastTest(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 가장 가까운 충돌 정보를 반환하는 레이캐스트입니다.
    static bool Raycast(RaycastHit& hit, const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 광선에 닿는 모든 충돌 정보를 반환하는 레이캐스트입니다.
    static std::vector<RaycastHit> RaycastAll(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);
    
    // 빠른 점 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    static bool OverlapPointTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    static Collider* OverlapPoint(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 점에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    static std::vector<Collider*> OverlapPointAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // 빠른 지오메트리 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    static bool OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    static Collider* OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 지오메트리에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    static std::vector<Collider*> OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // 빠른 콜라이더 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    static bool OverlapColliderTest(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    static Collider* OverlapCollider(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 콜라이더에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    static std::vector<Collider*> OverlapColliderAll(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    static bool OverlapSphereTest(float radius, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static Collider* OverlapSphere(float radius, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<Collider*> OverlapSphereAll(float radius, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    static bool OverlapBoxTest(const Vec3& extents, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static Collider* OverlapBox(const Vec3& extents, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<Collider*> OverlapBoxAll(const Vec3& extents, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    static bool OverlapCapsuleTest(float radius, float halfHeight, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static Collider* OverlapCapsule(float radius, float halfHeight, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<Collider*> OverlapCapsuleAll(float radius, float halfHeight, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // Sweep Query에서 허용되는 모양은 상자, 구, 캡슐, 및 Convex Geometry 입니다.

    static bool SweepGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static bool SweepGeometry(SweepHit& hit, PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<SweepHit> SweepGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    static bool SweepColliderTest(Collider* collider, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    static bool SweepCollider(SweepHit& hit, Collider* collider, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    static std::vector<SweepHit> SweepColliderAll(Collider* collider, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);
    
    static bool SweepSphereTest(float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static bool SweepSphere(SweepHit& hit, float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<SweepHit> SweepSphereAll(float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    static bool SweepBoxTest(const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static bool SweepBox(SweepHit& hit, const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<SweepHit> SweepBoxAll(const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    static bool SweepCapsuleTest(float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static bool SweepCapsule(SweepHit& hit, float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    static std::vector<SweepHit> SweepCapsuleAll(float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance = FLT_MAX, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

private:

    const static PxHitFlags bufferFlags;

    const static PxQueryFilterData defaultFilterData;

    const static PxQueryFilterData fastFilterData;
};

