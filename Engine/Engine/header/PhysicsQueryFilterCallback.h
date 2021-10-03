#pragma once

class PhysicsQueryFilterCallback : public PxQueryFilterCallback
{
public:

	// Set all to target
	PhysicsQueryFilterCallback(bool queryOnce);

	// Set specipic
	PhysicsQueryFilterCallback(PxU32 targetLayerBits, bool queryOnce);

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

	PxQueryHitType::Enum m_hitType;
};

