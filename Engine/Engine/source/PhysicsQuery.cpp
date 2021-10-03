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

    // eMESH_BOTH_SIDES : �ﰢ���� ���ʿ��� ������ �� �ֽ��ϴ�.
    PxHitFlags flags = 
        PxHitFlag::ePOSITION |
        PxHitFlag::eNORMAL |
        PxHitFlag::eFACE_INDEX |
        PxHitFlag::eMESH_BOTH_SIDES;

    // eANY_HIT  : �Ÿ��� ������� ó�� �����ϸ� �����մϴ�.
    // eNO_BLOCK : ��� ��Ʈ�� ���Ϳ� ������� ��ġ�� ����˴ϴ�.
    PxQueryFilterData filterData;
    filterData.flags =
        PxQueryFlag::eDYNAMIC |
        PxQueryFlag::eSTATIC |
        PxQueryFlag::ePREFILTER;

    PhysicsQueryFilterCallback filterCallback(layerMask, true);

    scene->raycast(pxRayPoint, pxRayDir, maxDistance, hit, flags, filterData, &filterCallback);

    return false;
}
