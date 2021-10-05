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
    return PhysicsQuery::OverlapSphereTest(point, radius, layerMask, queryType, ignoreBody);
}

Collider* Physics::OverlapSphere(const Vec3& point, float radius, PxU32 layerMask, PhysicsQueryType queryType, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapSphere(point, radius, layerMask, queryType, ignoreBody);
}

std::vector<Collider*> Physics::OverlapSphereAll(const Vec3& point, float radius, PxU32 layerMask, PhysicsQueryType queryType, unsigned int maxHit, Rigidbody* ignoreBody)
{
    return PhysicsQuery::OverlapSphereAll(point, radius, layerMask, queryType, maxHit, ignoreBody);
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
