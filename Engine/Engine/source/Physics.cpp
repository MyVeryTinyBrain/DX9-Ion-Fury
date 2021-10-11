#include "EngineBase.h"
#include "Physics.h"
#include "PhysicsDefines.h" 
#include "PhysicsDevice.h"
#include "LayerManager.h"
#include "PhysicsQuery.h"

void Physics::SetGravity(const Vec3& value)
{
    PhysicsDevice::GetInstance()->scene->setGravity(ToPxVec3(value));
}

Vec3 Physics::GetGravity()
{
    PxVec3 pxGravity = PhysicsDevice::GetInstance()->scene->getGravity();
    Vec3 value = FromPxVec3(pxGravity);
    return value;
}

void Physics::ResetLayerCollisions()
{
    PhysicsDevice::GetInstance()->layerManager->Reset();
}

void Physics::SetLayerCollisions(unsigned int layerIndexA, unsigned int layerIndexB, bool collision)
{
    PhysicsDevice::GetInstance()->layerManager->SetLayerCollisions(layerIndexA, layerIndexB, collision);
}

bool Physics::IsCollisionLayers(unsigned int layerIndexA, unsigned int layerIndexB)
{
    return PhysicsDevice::GetInstance()->layerManager->IsCollisionLayers(layerIndexA, layerIndexB);
}

uint32_t Physics::GetCollisionBits(unsigned int layerIndex)
{
    return PhysicsDevice::GetInstance()->layerManager->GetCollisionBits(layerIndex);
}

bool Physics::RaycastTest(const PhysicsRay& ray, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::RaycastTest(ray, layerMask, queryType, ignoreBody);
}

bool Physics::Raycast(RaycastHit& hit, const PhysicsRay& ray, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::Raycast(hit, ray, layerMask, queryType, ignoreBody);
}

std::vector<RaycastHit> Physics::RaycastAll(const PhysicsRay& ray, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::RaycastAll(ray, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::OverlapPointTest(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapPointTest(point, layerMask, queryType, ignoreBody);
}

Collider* Physics::OverlapPoint(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapPoint(point, layerMask, queryType, ignoreBody);
}

std::vector<Collider*> Physics::OverlapPointAll(const Vec3& point, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapPointAll(point, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::OverlapGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapGeometryTest(geometry, point, rotation, layerMask, queryType, ignoreBody);
}

Collider* Physics::OverlapGeometry(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapGeometry(geometry, point, rotation, layerMask, queryType, ignoreBody);
}

std::vector<Collider*> Physics::OverlapGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapGeometryAll(geometry, point, rotation, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::OverlapColliderTest(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType)
{
    return PhysicsQuery::OverlapColliderTest(collider, layerMask, queryType);
}

Collider* Physics::OverlapCollider(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType)
{
    return PhysicsQuery::OverlapCollider(collider, layerMask, queryType);
}

std::vector<Collider*> Physics::OverlapColliderAll(Collider* collider, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
{
    return PhysicsQuery::OverlapColliderAll(collider, layerMask, queryType, maxHit);
}

bool Physics::OverlapSphereTest(const Vec3& point, float radius, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapSphereTest(radius, point, layerMask, queryType, ignoreBody);
}

Collider* Physics::OverlapSphere(const Vec3& point, float radius, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapSphere(radius, point, layerMask, queryType, ignoreBody);
}

std::vector<Collider*> Physics::OverlapSphereAll(const Vec3& point, float radius, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapSphereAll(radius, point, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::OverlapBoxTest(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapBoxTest(point, extents, rotation, layerMask, queryType, ignoreBody);
}

Collider* Physics::OverlapBox(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapBox(point, extents, rotation, layerMask, queryType, ignoreBody);
}

std::vector<Collider*> Physics::OverlapBoxAll(const Vec3& point, const Vec3& extents, const Quat& rotation, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapBoxAll(point, extents, rotation, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::SweepGeometryTest(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepGeometryTest(geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

bool Physics::SweepGeometry(SweepHit& hit, PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepGeometry(hit, geometry, point, rotation, direction, distance, layerMask, queryType, ignoreBody);;
}

std::vector<SweepHit> Physics::SweepGeometryAll(PxGeometryHolder geometry, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepGeometryAll(geometry, point, rotation, direction, distance, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::SweepColliderTest(Collider* collider, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType)
{
    return PhysicsQuery::SweepColliderTest(collider, direction, distance, layerMask, queryType);
}

bool Physics::SweepCollider(SweepHit& hit, Collider* collider, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType)
{
    return PhysicsQuery::SweepCollider(hit, collider, direction, distance, layerMask, queryType);
}

std::vector<SweepHit> Physics::SweepColliderAll(Collider* collider, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit)
{
    return PhysicsQuery::SweepColliderAll(collider, direction, distance, layerMask, queryType);
}

bool Physics::SweepSphereTest(float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepSphereTest(radius, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

bool Physics::SweepSphere(SweepHit& hit, float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepSphere(hit, radius, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

std::vector<SweepHit> Physics::SweepSphereAll(float radius, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepSphereAll(radius, point, rotation, direction, distance, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::SweepBoxTest(const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepBoxTest(extents, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

bool Physics::SweepBox(SweepHit& hit, const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepBox(hit, extents, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

std::vector<SweepHit> Physics::SweepBoxAll(const Vec3& extents, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepBoxAll(extents, point, rotation, direction, distance, layerMask, queryType, maxHit, ignoreBody);
}

bool Physics::SweepCapsuleTest(float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepCapsuleTest(radius, halfHeight, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

bool Physics::SweepCapsule(SweepHit& hit, float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepCapsule(hit, radius, halfHeight, point, rotation, direction, distance, layerMask, queryType, ignoreBody);
}

std::vector<SweepHit> Physics::SweepCapsuleAll(float radius, float halfHeight, const Vec3& point, const Quat& rotation, const Vec3& direction, float distance, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::SweepCapsuleAll(radius, halfHeight, point, rotation, direction, distance, layerMask, queryType, maxHit, ignoreBody);
}
