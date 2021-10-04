#include "EngineBase.h"
#include "PhysicsQuery.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "PhysicsQueryFilterCallback.h"
#include "Collider.h"

bool PhysicsQuery::Raycast(const Ray& ray, PxU32 layerMask, PhysicsQueryType queryType)
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

std::vector<RaycastHit> PhysicsQuery::RaycastAll(const Ray& ray, PxU32 layerMask, PhysicsQueryType queryType)
{
    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(ray.point);
    PxVec3 pxRayDir = ToPxVec3(ray.direction);
    PhysicsQueryFilterCallback filterCallback(layerMask, queryType, false);

    constexpr unsigned int hitsMax = 256;
    PxRaycastHit hitsBuffer[hitsMax] = {};
    PxRaycastBuffer hitBuffer(hitsBuffer, hitsMax);

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
