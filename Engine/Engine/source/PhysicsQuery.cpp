#include "EngineBase.h"
#include "PhysicsQuery.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "PhysicsQueryFilterCallback.h"
#include "Collider.h"
#include "Transform.h"

const PxHitFlags PhysicsQuery::bufferFlags =
PxHitFlag::ePOSITION |          // 충돌 위치를 저장합니다.
PxHitFlag::eNORMAL |            // 충돌 노멀을 저장합니다.
PxHitFlag::eFACE_INDEX |        // 충돌한 폴리곤의 인덱스를 저장합니다
PxHitFlag::eMESH_BOTH_SIDES;    // 삼각형의 양쪽에서 적중할 수 있습니다.

const PxQueryFilterData PhysicsQuery::defaultFilterData
(
    PxQueryFlag::eDYNAMIC |         // 동적 바디에 적중할수 있습니다.
    PxQueryFlag::eSTATIC |          // 정적 바디에 적중할수 있습니다.
    PxQueryFlag::ePREFILTER         // 사전 필터링만을 사용합니다.
);

const PxQueryFilterData PhysicsQuery::fastFilterData
(
    PxQueryFlag::eDYNAMIC |         // 동적 바디에 적중할수 있습니다.
    PxQueryFlag::eSTATIC |          // 정적 바디에 적중할수 있습니다.
    PxQueryFlag::ePREFILTER |       // 사전 필터링만을 사용합니다.
    PxQueryFlag::eANY_HIT           // 거리에 상관없이 처음 적중하면 종료합니다.
);

bool PhysicsQuery::RaycastTest(const PhysicsRay& ray, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    // https://gameworksdocs.nvidia.com/PhysX/4.1/documentation/physxguide/Manual/SceneQueries.html

    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(ray.point);
    PxVec3 pxRayDir = ToPxVec3(ray.direction);
    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true, ignoreBody);
    PxRaycastBuffer hitBuffer;

    bool result = scene->raycast(pxRayPoint, pxRayDir, ray.distance, hitBuffer, bufferFlags, fastFilterData, &filterCallback);
    return result;
}

bool PhysicsQuery::Raycast(RaycastHit& hit, const PhysicsRay& ray, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(ray.point);
    PxVec3 pxRayDir = ToPxVec3(ray.direction);
    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true, ignoreBody);
    PxRaycastBuffer hitBuffer;

    bool result = scene->raycast(pxRayPoint, pxRayDir, ray.distance, hitBuffer, bufferFlags, defaultFilterData, &filterCallback);

    if (result)
    {
        const PxRaycastHit& pxHit = hitBuffer.getAnyHit(0);
        hit.point = FromPxVec3(pxHit.position);
        hit.normal = FromPxVec3(pxHit.normal);
        hit.distance = pxHit.distance;
        hit.collider = (Collider*)pxHit.shape->userData;
    }

    return result;
}

std::vector<RaycastHit> PhysicsQuery::RaycastAll(const PhysicsRay& ray, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(ray.point);
    PxVec3 pxRayDir = ToPxVec3(ray.direction);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false, ignoreBody);

    PxRaycastHit* hitsBuffer = new PxRaycastHit[maxHit]{};
    PxRaycastBuffer hitBuffer(hitsBuffer, maxHit);

    bool result = scene->raycast(pxRayPoint, pxRayDir, ray.distance, hitBuffer, bufferFlags, defaultFilterData, &filterCallback);
    PxU32 nbHits = hitBuffer.getNbAnyHits();

    std::vector<RaycastHit> hits;
    hits.resize(nbHits);
    for (PxU32 i = 0; i < nbHits; ++i)
    {
        const PxRaycastHit& pxHit = hitsBuffer[i];
        RaycastHit& hit = hits[i];
        hit.point = FromPxVec3(pxHit.position);
        hit.normal = FromPxVec3(pxHit.normal);
        hit.distance = pxHit.distance;
        hit.collider = (Collider*)pxHit.shape->userData;
    }

    SafeDeleteArray(hitsBuffer);

    return hits;
}

bool PhysicsQuery::OverlapPointTest(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxSphereGeometry geometry;
    geometry.radius = 0.001f;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false, ignoreBody);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry, pose, overlapBuffer, fastFilterData, &filterCallback);

    return result;
}

Collider* PhysicsQuery::OverlapPoint(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxSphereGeometry geometry;
    geometry.radius = 0.001f;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false, ignoreBody);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry, pose, overlapBuffer, fastFilterData, &filterCallback);

    if (result)
    {
        const PxOverlapHit& hit = overlapBuffer.getAnyHit(0);
        Collider* collider = (Collider*)hit.shape->userData;
        return collider;
    }

    return nullptr;
}

std::vector<Collider*> PhysicsQuery::OverlapPointAll(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxSphereGeometry geometry;
    geometry.radius = 0.001f;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false, ignoreBody);

    PxOverlapHit* hitsBuffer = new PxOverlapHit[maxHit]{};
    PxOverlapBuffer hitBuffer(hitsBuffer, maxHit);

    bool result = scene->overlap(geometry, pose, hitBuffer, defaultFilterData, &filterCallback);
    PxU32 nbHits = hitBuffer.getNbAnyHits();

    std::vector<Collider*> hits;
    hits.resize(nbHits);
    for (PxU32 i = 0; i < nbHits; ++i)
    {
        const PxOverlapHit& pxHit = hitsBuffer[i];
        Collider* collider = (Collider*)pxHit.shape->userData;
        hits[i] = collider;
    }

    SafeDeleteArray(hitsBuffer);

    return hits;
}

bool PhysicsQuery::OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = ToPxQuat(rotation);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true, ignoreBody);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry.any(), pose, overlapBuffer, fastFilterData, &filterCallback);

    return result;
}

Collider* PhysicsQuery::OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true, ignoreBody);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry.any(), pose, overlapBuffer, fastFilterData, &filterCallback);

    if (result)
    {
        const PxOverlapHit& hit = overlapBuffer.getAnyHit(0);
        return (Collider*)hit.shape;
    }

    return nullptr;
}

std::vector<Collider*> PhysicsQuery::OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false, ignoreBody);

    PxOverlapHit* hitsBuffer = new PxOverlapHit[maxHit]{};
    PxOverlapBuffer hitBuffer(hitsBuffer, maxHit);

    bool result = scene->overlap(geometry.any(), pose, hitBuffer, defaultFilterData, &filterCallback);
    PxU32 nbHits = hitBuffer.getNbAnyHits();

    std::vector<Collider*> hits;
    hits.resize(nbHits);
    for (PxU32 i = 0; i < nbHits; ++i)
    {
        const PxOverlapHit& pxHit = hitsBuffer[i];
        Collider* collider = (Collider*)pxHit.shape->userData;
        hits[i] = collider;
    }

    SafeDeleteArray(hitsBuffer);

    return hits;
}

bool PhysicsQuery::OverlapColliderTest(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType)
{
    return OverlapGeometryTest(collider->geometry, collider->transform->position, collider->transform->rotation, layerMask, queryType, collider->rigidbody);
}

Collider* PhysicsQuery::OverlapCollider(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType)
{
    return OverlapGeometry(collider->geometry, collider->transform->position, collider->transform->rotation, layerMask, queryType, collider->rigidbody);
}

std::vector<Collider*> PhysicsQuery::OverlapColliderAll(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
{
    return OverlapGeometryAll(collider->geometry, collider->transform->position, collider->transform->rotation, layerMask, queryType, maxHit, collider->rigidbody);
}

bool PhysicsQuery::OverlapSphereTest(float radius, const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxSphereGeometry geometry;
    geometry.radius = radius;
    return OverlapGeometryTest(geometry, point, Quat::Identity(), layerMask, queryType, ignoreBody);
}

Collider* PhysicsQuery::OverlapSphere(float radius, const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxSphereGeometry geometry;
    geometry.radius = radius;
    return OverlapGeometry(geometry, point, Quat::Identity(), layerMask, queryType, ignoreBody);
}

std::vector<Collider*> PhysicsQuery::OverlapSphereAll(float radius, const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    PxSphereGeometry geometry;
    geometry.radius = radius;
    return OverlapGeometryAll(geometry, point, Quat::Identity(), layerMask, queryType, maxHit, ignoreBody);
}

bool PhysicsQuery::OverlapBoxTest(const Vec3& extents, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxBoxGeometry geometry;
    geometry.halfExtents = ToPxVec3(extents) * 0.5f;
    return OverlapGeometryTest(geometry, point, Quat::Identity(), layerMask, queryType, ignoreBody);
}

Collider* PhysicsQuery::OverlapBox(const Vec3& extents, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxBoxGeometry geometry;
    geometry.halfExtents = ToPxVec3(extents) * 0.5f;
    return OverlapGeometry(geometry, point, Quat::Identity(), layerMask, queryType, ignoreBody);
}

std::vector<Collider*> PhysicsQuery::OverlapBoxAll(const Vec3& extents, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    PxBoxGeometry geometry;
    geometry.halfExtents = ToPxVec3(extents) * 0.5f;
    return OverlapGeometryAll(geometry, point, Quat::Identity(), layerMask, queryType, maxHit, ignoreBody);
}

bool PhysicsQuery::OverlapCapsuleTest(float radius, float halfHeight, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxCapsuleGeometry geometry;
    geometry.radius = radius;
    geometry.halfHeight = halfHeight;
    Quat capsuleRotate = rotation * Quat::FromEuler(0, 0, 90);
    return OverlapGeometryTest(geometry, point, capsuleRotate, layerMask, queryType, ignoreBody);
}

Collider* PhysicsQuery::OverlapCapsule(float radius, float halfHeight, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxCapsuleGeometry geometry;
    geometry.radius = radius;
    geometry.halfHeight = halfHeight;
    Quat capsuleRotate = rotation * Quat::FromEuler(0, 0, 90);
    return OverlapGeometry(geometry, point, capsuleRotate, layerMask, queryType, ignoreBody);
}

std::vector<Collider*> PhysicsQuery::OverlapCapsuleAll(float radius, float halfHeight, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    PxCapsuleGeometry geometry;
    geometry.radius = radius;
    geometry.halfHeight = halfHeight;
    Quat capsuleRotate = rotation * Quat::FromEuler(0, 0, 90);
    return OverlapGeometryAll(geometry, point, capsuleRotate, layerMask, queryType, maxHit, ignoreBody);
}

bool PhysicsQuery::SweepGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = ToPxQuat(rotation);

    PxVec3 dir = ToPxVec3(direction);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true, ignoreBody);
    PxSweepBuffer hitBuffer;

    bool result = scene->sweep(geometry.any(), pose, dir, distance, hitBuffer, bufferFlags, fastFilterData, &filterCallback);
    return result;
}

bool PhysicsQuery::SweepGeometry(SweepHit& hit, PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = ToPxQuat(rotation);

    PxVec3 dir = ToPxVec3(direction);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true, ignoreBody);
    PxSweepBuffer hitBuffer;

    bool result = scene->sweep(geometry.any(), pose, dir, distance, hitBuffer, bufferFlags, defaultFilterData, &filterCallback);

    if (result)
    {
        const PxSweepHit& pxHit = hitBuffer.getAnyHit(0);
        hit.point = FromPxVec3(pxHit.position);
        hit.normal = FromPxVec3(pxHit.normal);
        hit.distance = pxHit.distance;
        hit.collider = (Collider*)pxHit.shape->userData;
    }

    return result;
}

std::vector<SweepHit> PhysicsQuery::SweepGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = ToPxQuat(rotation);

    PxVec3 dir = ToPxVec3(direction);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false, ignoreBody);
    PxSweepHit* hitsBuffer = new PxSweepHit[maxHit]{};
    PxSweepBuffer hitBuffer(hitsBuffer, maxHit);

    bool result = scene->sweep(geometry.any(), pose, dir, distance, hitBuffer, bufferFlags, defaultFilterData, &filterCallback);
    PxU32 nbHits = hitBuffer.getNbAnyHits();

    std::vector<SweepHit> hits;
    hits.resize(nbHits);
    for (PxU32 i = 0; i < nbHits; ++i)
    {
        const PxSweepHit& pxHit = hitsBuffer[i];
        SweepHit& hit = hits[i];
        hit.point = FromPxVec3(pxHit.position);
        hit.normal = FromPxVec3(pxHit.normal);
        hit.distance = pxHit.distance;
        hit.collider = (Collider*)pxHit.shape->userData;
    }

    SafeDeleteArray(hitsBuffer);

    return hits;
}

bool PhysicsQuery::SweepColliderTest(Collider* collider, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType)
{
    return SweepGeometryTest(collider->geometry, collider->transform->position, collider->transform->rotation, direction, distance, layerMask, queryType, collider->rigidbody);
}

bool PhysicsQuery::SweepCollider(SweepHit& hit, Collider* collider, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType)
{
    return SweepGeometry(hit, collider->geometry, collider->transform->position, collider->transform->rotation, direction, distance, layerMask, queryType, collider->rigidbody);
}

std::vector<SweepHit> PhysicsQuery::SweepColliderAll(Collider* collider, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
{
    return SweepGeometryAll(collider->geometry, collider->transform->position, collider->transform->rotation, direction, distance, layerMask, queryType, maxHit, collider->rigidbody);
}

bool PhysicsQuery::SweepSphereTest(float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxSphereGeometry geometry;
    geometry.radius = radius;
    return SweepGeometryTest(geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

bool PhysicsQuery::SweepSphere(SweepHit& hit, float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxSphereGeometry geometry;
    geometry.radius = radius;
    return SweepGeometry(hit, geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

std::vector<SweepHit> PhysicsQuery::SweepSphereAll(float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    PxSphereGeometry geometry;
    geometry.radius = radius;
    return SweepGeometryAll(geometry, point, rotation, direction, distance, layerMask, queryType, maxHit, ignoreBody);
}

bool PhysicsQuery::SweepBoxTest(const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxBoxGeometry geometry;
    geometry.halfExtents = ToPxVec3(extents) * 0.5f;
    return SweepGeometryTest(geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

bool PhysicsQuery::SweepBox(SweepHit& hit, const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxBoxGeometry geometry;
    geometry.halfExtents = ToPxVec3(extents) * 0.5f;
    return SweepGeometry(hit, geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

std::vector<SweepHit> PhysicsQuery::SweepBoxAll(const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    PxBoxGeometry geometry;
    geometry.halfExtents = ToPxVec3(extents) * 0.5f;
    return SweepGeometryAll(geometry, point, rotation, direction, distance, layerMask, queryType, maxHit, ignoreBody);
}

bool PhysicsQuery::SweepCapsuleTest(float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxCapsuleGeometry geometry;
    geometry.radius = radius;
    geometry.halfHeight = halfHeight;
    Quat capsuleRotate = rotation * Quat::FromEuler(0, 0, 90);
    return SweepGeometryTest(geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

bool PhysicsQuery::SweepCapsule(SweepHit& hit, float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    PxCapsuleGeometry geometry;
    geometry.radius = radius;
    geometry.halfHeight = halfHeight;
    Quat capsuleRotate = rotation * Quat::FromEuler(0, 0, 90);
    return SweepGeometry(hit, geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

std::vector<SweepHit> PhysicsQuery::SweepCapsuleAll(float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    PxCapsuleGeometry geometry;
    geometry.radius = radius;
    geometry.halfHeight = halfHeight;
    Quat capsuleRotate = rotation * Quat::FromEuler(0, 0, 90);
    return SweepGeometryAll(geometry, point, rotation, direction, distance, layerMask, queryType, maxHit, ignoreBody);
}
