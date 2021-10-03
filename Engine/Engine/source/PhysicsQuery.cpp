#include "EngineBase.h"
#include "PhysicsQuery.h"
#include "PhysicsDevice.h"
#include "PhysicsDefines.h"
#include "PhysicsQueryFilterCallback.h"

bool PhysicsQuery::Raycast(const Vec3& rayPoint, const Vec3& rayDir, float maxDistance, PxU32 layerMask)
{
    // https://gameworksdocs.nvidia.com/PhysX/4.1/documentation/physxguide/Manual/SceneQueries.html

    auto device = PhysicsDevice::GetInstance();
    auto scene = device->scene;

    PxVec3 pxRayPoint = ToPxVec3(rayPoint);
    PxVec3 pxRayDir = ToPxVec3(rayDir);
    PxRaycastBuffer hit;

    // eMESH_BOTH_SIDES : 삼각형의 양쪽에서 적중할 수 있습니다.
    PxHitFlags flags = 
        PxHitFlag::ePOSITION |
        PxHitFlag::eNORMAL |
        PxHitFlag::eFACE_INDEX |
        PxHitFlag::eMESH_BOTH_SIDES;

    // eANY_HIT  : 거리에 상관없이 처음 적중하면 종료합니다.
    // eNO_BLOCK : 모든 히트가 필터에 관계없이 터치로 보고됩니다.
    PxQueryFilterData filterData;
    filterData.flags =
        PxQueryFlag::eDYNAMIC |
        PxQueryFlag::eSTATIC |
        PxQueryFlag::ePREFILTER;

    PhysicsQueryFilterCallback filterCallback(layerMask, true);

    scene->raycast(pxRayPoint, pxRayDir, maxDistance, hit, flags, filterData, &filterCallback);

    return false;
}
