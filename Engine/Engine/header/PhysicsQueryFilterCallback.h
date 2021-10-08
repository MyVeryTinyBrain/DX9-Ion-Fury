#pragma once

#include "PhysicsQueryTypes.h"

class PhysicsQueryFilterCallback : public PxQueryFilterCallback
{
public:

	// Set all to target
	PhysicsQueryFilterCallback(PhysicsQueryType queryType, bool queryOnce, class Rigidbody* ignoreBody = nullptr);

	// Set specipic
	PhysicsQueryFilterCallback(PxU32 targetLayerBits, PhysicsQueryType queryType, bool queryOnce, class Rigidbody* ignoreBody = nullptr);

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

	class Rigidbody* m_ignoreBody = nullptr;
};

