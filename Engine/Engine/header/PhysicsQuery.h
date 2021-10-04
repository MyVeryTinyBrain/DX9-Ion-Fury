#pragma once

#include "PhysicsQueryTypes.h"

namespace PhysicsQuery
{
    // 빠른 레이캐스트입니다.
    // 충돌 정보를 반환하지 않습니다.
	bool Raycast(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 충돌 정보를 반환하는 레이캐스트입니다.
	bool Raycast(RaycastHit& hit, const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 광선에 닿는 모든 충돌 정보를 반환하는 레이캐스트입니다.
    std::vector<RaycastHit> RaycastAll(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    const PxHitFlags bufferFlags =
        PxHitFlag::ePOSITION |          // 충돌 위치를 저장합니다.
        PxHitFlag::eNORMAL |            // 충돌 노멀을 저장합니다.
        PxHitFlag::eFACE_INDEX |        // 충돌한 폴리곤의 인덱스를 저장합니다
        PxHitFlag::eMESH_BOTH_SIDES;    // 삼각형의 양쪽에서 적중할 수 있습니다.

    const PxQueryFilterData defaultFilterData
    (
        PxQueryFlag::eDYNAMIC |         // 동적 바디에 적중할수 있습니다.
        PxQueryFlag::eSTATIC |          // 정적 바디에 적중할수 있습니다.
        PxQueryFlag::ePREFILTER         // 사전 필터링만을 사용합니다.
    );

    const PxQueryFilterData fastFilterData
    (
        PxQueryFlag::eDYNAMIC |         // 동적 바디에 적중할수 있습니다.
        PxQueryFlag::eSTATIC |          // 정적 바디에 적중할수 있습니다.
        PxQueryFlag::ePREFILTER |       // 사전 필터링만을 사용합니다.
        PxQueryFlag::eANY_HIT           // 거리에 상관없이 처음 적중하면 종료합니다.
    );
};

