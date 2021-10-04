#include "EngineBase.h"
#include "PhysicsQuery.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "PhysicsQueryFilterCallback.h"
#include "Collider.h"

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

bool PhysicsQuery::RaycastTest(const Ray& ray, PxU32 layerMask, PhysicsQueryType queryType)
{
    // https://gameworksdocs.nvidia.com/PhysX/4.1/documentation/physxguide/Manual/SceneQueries.html

    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(ray.point);
    PxVec3 pxRayDir = ToPxVec3(ray.direction);
    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true);
    PxRaycastBuffer hitBuffer;

    bool result = scene->raycast(pxRayPoint, pxRayDir, ray.distance, hitBuffer, bufferFlags, fastFilterData, &filterCallback);
    return result;
}

bool PhysicsQuery::Raycast(RaycastHit& hit, const Ray& ray, PxU32 layerMask, PhysicsQueryType queryType)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(ray.point);
    PxVec3 pxRayDir = ToPxVec3(ray.direction);
    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true);
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

std::vector<RaycastHit> PhysicsQuery::RaycastAll(const Ray& ray, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(ray.point);
    PxVec3 pxRayDir = ToPxVec3(ray.direction);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false);

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

    return hits;
}

bool PhysicsQuery::OverlapPointTest(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxSphereGeometry geometry;
    geometry.radius = 0.001f;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry, pose, overlapBuffer, fastFilterData, &filterCallback);

    return result;
}

Collider* PhysicsQuery::OverlapPoint(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxSphereGeometry geometry;
    geometry.radius = 0.001f;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry, pose, overlapBuffer, defaultFilterData, &filterCallback);

    if (result)
    {
        const PxOverlapHit& hit = overlapBuffer.getAnyHit(0);
        Collider* collider = (Collider*)hit.shape->userData;
        return collider;
    }

    return nullptr;
}

std::vector<Collider*> PhysicsQuery::OverlapPointAll(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit = 64)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxSphereGeometry geometry;
    geometry.radius = 0.001f;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false);

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
    }

    return hits;
}

bool PhysicsQuery::OverlapPointTest(Collider* collider, const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType)
{
    return false;
}

Collider* PhysicsQuery::OverlapPoint(Collider* collider, const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType)
{
    return nullptr;
}

std::vector<Collider*> PhysicsQuery::OverlapPointAll(Collider* collider, const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
{
    return std::vector<Collider*>();
}
