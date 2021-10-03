#include "EngineBase.h"
#include "PhysicsQueryFilterCallback.h"
#include "Collider.h"
#include "Rigidbody.h"

PhysicsQueryFilterCallback::PhysicsQueryFilterCallback(bool queryOnce)
{
    m_targets = 0xFFFFFFFF;
    m_hitType = queryOnce ? PxQueryHitType::eBLOCK : PxQueryHitType::eTOUCH;
}

PhysicsQueryFilterCallback::PhysicsQueryFilterCallback(PxU32 targetLayerBits, bool queryOnce)
{
    m_targets = targetLayerBits;
    m_hitType = queryOnce ? PxQueryHitType::eBLOCK : PxQueryHitType::eTOUCH;
}

PxQueryHitType::Enum PhysicsQueryFilterCallback::preFilter(
    const PxFilterData& filterData, 
    const PxShape* shape, 
    const PxRigidActor* actor, 
    PxHitFlags& queryFlags)
{
    Collider* collider = (Collider*)shape->userData;
    Rigidbody* rigidbody = (Rigidbody*)actor->userData;

    if(!collider->isWake || !rigidbody->isWake)
        return PxQueryHitType::eNONE;

    if (filterData.word0 & m_targets)
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
