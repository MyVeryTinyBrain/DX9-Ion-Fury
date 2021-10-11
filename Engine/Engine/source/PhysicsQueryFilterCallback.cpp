#include "EngineBase.h"
#include "PhysicsQueryFilterCallback.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "PhysicsDevice.h"
#include "LayerManager.h"

PhysicsQueryFilterCallback::PhysicsQueryFilterCallback(PhysicsQueryType queryType, bool queryOnce, Rigidbody* ignoreBody)
{
    m_targets = 0xFFFFFFFF;
    m_queryType = queryType;
    m_hitType = queryOnce ? PxQueryHitType::eBLOCK : PxQueryHitType::eTOUCH;
    m_ignoreBody = ignoreBody;
}

PhysicsQueryFilterCallback::PhysicsQueryFilterCallback(PxU32 targetLayerBits, PhysicsQueryType queryType, bool queryOnce, Rigidbody* ignoreBody)
{
    m_targets = targetLayerBits;
    m_queryType = queryType;
    m_hitType = queryOnce ? PxQueryHitType::eBLOCK : PxQueryHitType::eTOUCH;
    m_ignoreBody = ignoreBody;
}

PxQueryHitType::Enum PhysicsQueryFilterCallback::preFilter(
    const PxFilterData& filterData, 
    const PxShape* shape, 
    const PxRigidActor* actor, 
    PxHitFlags& queryFlags)
{
    auto device = PhysicsDevice::GetInstance();
    auto layerManager = device->layerManager;

    Collider* collider = (Collider*)shape->userData;
    Rigidbody* rigidbody = (Rigidbody*)actor->userData;

    wstring colName = collider->name;
    wstring bodyName = rigidbody->name;

    if (m_ignoreBody && rigidbody == m_ignoreBody)
        return PxQueryHitType::eNONE;

    bool allowTrigger = int(m_queryType) & int(PhysicsQueryType::Trigger);
    bool allowCollider = int(m_queryType) & int(PhysicsQueryType::Collider);

    if(!collider->isWake || !rigidbody->isWake)
        return PxQueryHitType::eNONE;

    if (!allowTrigger && collider->isTrigger)
        return PxQueryHitType::eNONE;

    if (!allowCollider && !collider->isTrigger)
        return PxQueryHitType::eNONE;

    //if (layerManager->GetCollisionBits(collider->layerIndex) & m_targets)
    //    return m_hitType;
    //else
    //    return PxQueryHitType::eNONE;

    if ((1 << collider->layerIndex) & m_targets)
        return m_hitType;
    else
        return PxQueryHitType::eNONE;
}

PxQueryHitType::Enum PhysicsQueryFilterCallback::postFilter(
    const PxFilterData& filterData, 
    const PxQueryHit& hit)
{
    // 이 콜백은 사용하지 않습니다.

    return PxQueryHitType::eTOUCH;
}
