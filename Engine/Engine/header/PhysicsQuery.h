#pragma once

#include "PhysicsQueryTypes.h"

class Collider;

class PhysicsQuery
{
public:

    // ���� ����ĳ��Ʈ�Դϴ�.
    // �浹 ������ ��ȯ���� �ʽ��ϴ�.
	bool RaycastTest(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ���� ����� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
	bool Raycast(RaycastHit& hit, const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ������ ��� ��� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
    std::vector<RaycastHit> RaycastAll(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);
    
    // ���� �� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    bool OverlapPointTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    Collider* OverlapPoint(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ���� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    std::vector<Collider*> OverlapPointAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    // ���� �ݶ��̴� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    bool OverlapPointTest(Collider* collider, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    Collider* OverlapPoint(Collider* collider, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // �ݶ��̴��� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    std::vector<Collider*> OverlapPointAll(Collider* collider, const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

private:

    const static PxHitFlags bufferFlags;

    const static PxQueryFilterData defaultFilterData;

    const static PxQueryFilterData fastFilterData;
};

