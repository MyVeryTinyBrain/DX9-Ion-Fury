#pragma once

class PhysicsFilterShaderCallback : public PxSimulationFilterCallback
{
	// ���������� �浹�� �� ��翡 ���ؼ� ó���մϴ�.
	// 1. �� ��� �ڽ��� ��ġ�� ��쿡 ȣ��˴ϴ�.
	// 2. �Ӽ��� ����Ǵ� ��� ȣ��˴ϴ�.
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
	// �浹 �̺�Ʈ ȣ�⿡ �ʿ��� �÷��׵��Դϴ�.
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

	// �� �÷��׵��� �Ӱ谪�� �������� �ݹ��� ȣ���մϴ�.
	// eNOTIFY_THRESHOLD_FORCE_FOUND 
	// eNOTIFY_THRESHOLD_FORCE_PERSISTS 
	// eNOTIFY_THRESHOLD_FORCE_LOST 
}

