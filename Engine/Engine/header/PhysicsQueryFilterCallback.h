#pragma once

#include "PhysicsQueryTypes.h"

class PhysicsQueryFilterCallback : public PxQueryFilterCallback
{
public:

	// Set all to target
	PhysicsQueryFilterCallback(PhysicsQueryType queryType, bool queryOnce);

	// Set specipic
	PhysicsQueryFilterCallback(PxU32 targetLayerBits, PhysicsQueryType queryType, bool queryOnce);

private:

	virtual PxQueryHitType::Enum preFilter(
		const PxFilterData& filterData, 
		const PxShape* shape, 
		const PxRigidActor* actor, 
		PxHitFlags& queryFlags
	) override;

	virtual PxQueryHitType::Enum postFilter(
		const PxFilterData& filterData, 
		const PxQueryHit& hit
	) override;

	PxU32 m_targets;

	PhysicsQueryType m_queryType;

	PxQueryHitType::Enum m_hitType;

public:

	class Collider* m_ignoreCollider = nullptr;
};

