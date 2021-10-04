#pragma once

#include "PhysicsQueryTypes.h"

class Collider;

class PhysicsQuery
{
public:

    // 빠른 레이캐스트입니다.
    // 충돌 정보를 반환하지 않습니다.
	bool RaycastTest(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 충돌 정보를 반환하는 레이캐스트입니다.
	bool Raycast(RaycastHit& hit, const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 광선에 닿는 모든 충돌 정보를 반환하는 레이캐스트입니다.
    std::vector<RaycastHit> RaycastAll(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);
    
    // 빠른 점 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    bool OverlapPointTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    Collider* OverlapPoint(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 점에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    std::vector<Collider*> OverlapPointAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    // 빠른 콜라이더 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    bool OverlapPointTest(Collider* collider, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    Collider* OverlapPoint(Collider* collider, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 콜라이더에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    std::vector<Collider*> OverlapPointAll(Collider* collider, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

private:

    const static PxHitFlags bufferFlags;

    const static PxQueryFilterData defaultFilterData;

    const static PxQueryFilterData fastFilterData;
};

