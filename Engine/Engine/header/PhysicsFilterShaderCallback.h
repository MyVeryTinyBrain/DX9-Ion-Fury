#pragma once

class PhysicsFilterShaderCallback : public PxSimulationFilterCallback
{
	// 잠재적으로 충돌할 두 모양에 대해서 처리합니다.
	// 1. 두 경계 박스가 겹치는 경우에 호출됩니다.
	// 2. 속성이 변경되는 경우 호출됩니다.
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

namespace PhysicsFilterShaderCallbackFilters
{
	// 충돌 이벤트 호출에 필요한 플래그들입니다.
	const PxU32 eNotifyFlags =
		PxPairFlag::eDETECT_DISCRETE_CONTACT |
		PxPairFlag::eNOTIFY_TOUCH_FOUND |
		PxPairFlag::eNOTIFY_TOUCH_LOST |
		PxPairFlag::eNOTIFY_CONTACT_POINTS;

	const PxPairFlags eTriggerFlags = 
		PxPairFlag::eTRIGGER_DEFAULT | 
		(PxPairFlag::Enum)eNotifyFlags;

	const PxPairFlags eContactFlags = 
		PxPairFlag::eCONTACT_DEFAULT | 
		(PxPairFlag::Enum)eNotifyFlags | 
		PxPairFlag::eDETECT_CCD_CONTACT | 
		PxPairFlag::eNOTIFY_TOUCH_PERSISTS;

	// 이 플래그들은 임계값을 기준으로 콜백을 호출합니다.
	// eNOTIFY_THRESHOLD_FORCE_FOUND 
	// eNOTIFY_THRESHOLD_FORCE_PERSISTS 
	// eNOTIFY_THRESHOLD_FORCE_LOST 
}

