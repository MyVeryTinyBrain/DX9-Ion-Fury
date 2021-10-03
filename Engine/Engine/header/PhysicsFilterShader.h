#pragma once

class PhysicsFilterShader : public PxSimulationFilterCallback
{
	virtual PxFilterFlags pairFound(
		PxU32 pairID, 
		PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor* a0, const PxShape* s0, 
		PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor* a1, const PxShape* s1, 
		PxPairFlags& pairFlags
	) override;
	
	virtual void pairLost(
		PxU32 pairID, 
		PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
		PxFilterObjectAttributes attributes1, PxFilterData filterData1, 
		bool objectRemoved
	) override;
	
	virtual bool statusChange(
		PxU32& pairID, 
		PxPairFlags& pairFlags, 
		PxFilterFlags& filterFlags
	) override;

public:

	static PxFilterFlags PxSimulationFilterShader(
		PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);
};

