#include "EngineBase.h"
#include "PhysicsQuery.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "PhysicsQueryFilterCallback.h"
#include "Collider.h"
#include "Transform.h"

const PxHitFlags PhysicsQuery::bufferFlags =
PxHitFlag::ePOSITION |          // �浹 ��ġ�� �����մϴ�.
PxHitFlag::eNORMAL |            // �浹 ����� �����մϴ�.
PxHitFlag::eFACE_INDEX |        // �浹�� �������� �ε����� �����մϴ�
PxHitFlag::eMESH_BOTH_SIDES;    // �ﰢ���� ���ʿ��� ������ �� �ֽ��ϴ�.

const PxQueryFilterData PhysicsQuery::defaultFilterData
(
    PxQueryFlag::eDYNAMIC |         // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
    PxQueryFlag::eSTATIC |          // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
    PxQueryFlag::ePREFILTER         // ���� ���͸����� ����մϴ�.
);

const PxQueryFilterData PhysicsQuery::fastFilterData
(
    PxQueryFlag::eDYNAMIC |         // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
    PxQueryFlag::eSTATIC |          // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
    PxQueryFlag::ePREFILTER |       // ���� ���͸����� ����մϴ�.
    PxQueryFlag::eANY_HIT           // �Ÿ��� ������� ó�� �����ϸ� �����մϴ�.
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

std::vector<Collider*> PhysicsQuery::OverlapPointAll(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
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

bool PhysicsQuery::OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Collider* ignoreCollider)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = ToPxQuat(rotation);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry.any(), pose, overlapBuffer, fastFilterData, &filterCallback);

    return result;
}

Collider* PhysicsQuery::OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Collider* ignoreCollider)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, true);

    PxOverlapBuffer overlapBuffer;

    bool result = scene->overlap(geometry.any(), pose, overlapBuffer, fastFilterData, &filterCallback);

    if (result)
    {
        const PxOverlapHit& hit = overlapBuffer.getAnyHit(0);
        return (Collider*)hit.shape;
    }

    return nullptr;
}

std::vector<Collider*> PhysicsQuery::OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Collider* ignoreCollider)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxTransform pose;
    pose.p = ToPxVec3(point);
    pose.q = PxQuat(PxIdentity);

    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false);

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
    }

    return hits;
}

bool PhysicsQuery::OverlapColliderTest(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType)
{
    return OverlapGeometryTest(collider->geometry, collider->transform->position, collider->transform->rotation, layerMask, queryType, collider);
}

Collider* PhysicsQuery::OverlapCollider(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType)
{
    return OverlapGeometry(collider->geometry, collider->transform->position, collider->transform->rotation, layerMask, queryType, collider);
}

std::vector<Collider*> PhysicsQuery::OverlapColliderAll(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
{
    return OverlapGeometryAll(collider->geometry, collider->transform->position, collider->transform->rotation, layerMask, queryType, maxHit, collider);
}
