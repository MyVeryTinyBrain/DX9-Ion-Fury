#pragma once

#include "PhysicsQueryTypes.h"

class Collider;
class Rigidbody;

namespace Physics
{
    void SetGravity(const Vec3& value);

    Vec3 GetGravity();

	// 0-0 ���̾�� �浹�� ������ ��� ���̾���� �浹�� ��Ȱ��ȭ �մϴ�.
	void ResetLayerCollisions();

	// A ���̾�� B ���̾��� �浹�� �����մϴ�.
	// A, B �� 32���� ���� �������� �մϴ�.
	// ���� Collider ������Ʈ�� ���ؼ� ApplyLayer �Լ��� ȣ���մϴ�.
	void SetLayerCollisions(unsigned int layerIndexA, unsigned int layerIndexB, bool collision);

	// A ���̾�� B ���̾��� �浹�� Ȯ���մϴ�.
	// A, B �� 32���� ���� �������� �մϴ�.
	bool IsCollisionLayers(unsigned int layerIndexA, unsigned int layerIndexB);

	// ���̾��� �浹 ��Ʈ�� ��ȯ�մϴ�.
	uint32_t GetCollisionBits(unsigned int layerIndex);

    // ���� ����ĳ��Ʈ�Դϴ�.
    // �浹 ������ ��ȯ���� �ʽ��ϴ�.
    bool RaycastTest(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ����� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
    bool Raycast(RaycastHit& hit, const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ������ ��� ��� �浹 ������ ��ȯ�ϴ� ����ĳ��Ʈ�Դϴ�.
    std::vector<RaycastHit> RaycastAll(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // ���� �� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    bool OverlapPointTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    Collider* OverlapPoint(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    std::vector<Collider*> OverlapPointAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // ���� ������Ʈ�� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    bool OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    Collider* OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // ������Ʈ���� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    std::vector<Collider*> OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // ���� �ݶ��̴� ��ħ �׽�Ʈ�Դϴ�.
    // ��ħ ������ ��ȯ���� �ʽ��ϴ�.
    bool OverlapColliderTest(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // ���� ����� ��ġ�� �ݶ��̴��� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    Collider* OverlapCollider(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // �ݶ��̴��� ��ġ�� ��� �ݶ��̴����� ��ȯ�ϴ� ��ħ �׽�Ʈ�Դϴ�.
    std::vector<Collider*> OverlapColliderAll(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    bool OverlapSphereTest(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    Collider* OverlapSphere(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    std::vector<Collider*> OverlapSphereAll(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    bool OverlapBoxTest(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    Collider* OverlapBox(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    std::vector<Collider*> OverlapBoxAll(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);
};

