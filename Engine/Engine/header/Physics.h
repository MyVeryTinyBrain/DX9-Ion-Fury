#pragma once

#include "PhysicsQueryTypes.h"

class Collider;
class Rigidbody;

namespace Physics
{
    void SetGravity(const Vec3& value);

    Vec3 GetGravity();

	// 0-0 레이어간의 충돌을 제외한 모든 레이어들의 충돌을 비활성화 합니다.
	void ResetLayerCollisions();

	// A 레이어와 B 레이어의 충돌을 설정합니다.
	// A, B 는 32보다 작은 정수여야 합니다.
	// 이후 Collider 컴포넌트에 대해서 ApplyLayer 함수를 호출합니다.
	void SetLayerCollisions(unsigned int layerIndexA, unsigned int layerIndexB, bool collision);

	// A 레이어와 B 레이어의 충돌을 확인합니다.
	// A, B 는 32보다 작은 정수여야 합니다.
	bool IsCollisionLayers(unsigned int layerIndexA, unsigned int layerIndexB);

	// 레이어의 충돌 비트를 반환합니다.
	uint32_t GetCollisionBits(unsigned int layerIndex);

    // 빠른 레이캐스트입니다.
    // 충돌 정보를 반환하지 않습니다.
    bool RaycastTest(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 가장 가까운 충돌 정보를 반환하는 레이캐스트입니다.
    bool Raycast(RaycastHit& hit, const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 광선에 닿는 모든 충돌 정보를 반환하는 레이캐스트입니다.
    std::vector<RaycastHit> RaycastAll(const PhysicsRay& ray, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // 빠른 점 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    bool OverlapPointTest(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    Collider* OverlapPoint(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 점에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    std::vector<Collider*> OverlapPointAll(const Vec3& point, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // 빠른 지오메트리 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    bool OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    Collider* OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    // 지오메트리에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    std::vector<Collider*> OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    // 빠른 콜라이더 겹침 테스트입니다.
    // 겹침 정보를 반환하지 않습니다.
    bool OverlapColliderTest(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 가장 가까운 겹치는 콜라이더를 반환하는 겹침 테스트입니다.
    Collider* OverlapCollider(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All);

    // 콜라이더에 겹치는 모든 콜라이더들을 반환하는 겹침 테스트입니다.
    std::vector<Collider*> OverlapColliderAll(Collider* collider, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64);

    bool OverlapSphereTest(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    Collider* OverlapSphere(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    std::vector<Collider*> OverlapSphereAll(const Vec3& point, float radius, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);

    bool OverlapBoxTest(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    Collider* OverlapBox(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, Rigidbody* ignoreBody = nullptr);

    std::vector<Collider*> OverlapBoxAll(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask = 0xFFFFFFFF, PhysicsQueryType queryType = PhysicsQueryType::All, unsigned int maxHit = 64, Rigidbody* ignoreBody = nullptr);
};

