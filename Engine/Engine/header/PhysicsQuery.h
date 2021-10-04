#pragma once

#include "PhysicsQueryTypes.h"

namespace PhysicsQuery
{
    // ���� ����ĳ��Ʈ�Դϴ�.
    // �浹 ������ ��ȯ���� �ʽ��ϴ�.
	bool Raycast(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ���� ����� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
	bool Raycast(RaycastHit& hit, const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ������ ��� ��� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
    std::vector<RaycastHit> RaycastAll(const Ray& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    const PxHitFlags bufferFlags =
        PxHitFlag::ePOSITION |          // �浹 ��ġ�� �����մϴ�.
        PxHitFlag::eNORMAL |            // �浹 ����� �����մϴ�.
        PxHitFlag::eFACE_INDEX |        // �浹�� �������� �ε����� �����մϴ�
        PxHitFlag::eMESH_BOTH_SIDES;    // �ﰢ���� ���ʿ��� ������ �� �ֽ��ϴ�.

    const PxQueryFilterData defaultFilterData
    (
        PxQueryFlag::eDYNAMIC |         // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
        PxQueryFlag::eSTATIC |          // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
        PxQueryFlag::ePREFILTER         // ���� ���͸����� ����մϴ�.
    );

    const PxQueryFilterData fastFilterData
    (
        PxQueryFlag::eDYNAMIC |         // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
        PxQueryFlag::eSTATIC |          // ���� �ٵ� �����Ҽ� �ֽ��ϴ�.
        PxQueryFlag::ePREFILTER |       // ���� ���͸����� ����մϴ�.
        PxQueryFlag::eANY_HIT           // �Ÿ��� ������� ó�� �����ϸ� �����մϴ�.
    );
};

