#include "EngineBase.h"
#include "PhysicsFilterShader.h"
#include "PhysicsDevice.h"
#include "LayerManager.h"
#include "Collider.h"

PxFilterFlags PhysicsFilterShader::pairFound(
	PxU32 pairID, 
	PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor* a0, const PxShape* s0, 
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor* a1, const PxShape* s1, 
	PxPairFlags& pairFlags)
{
	auto device = PhysicsDevice::GetInstance();
	auto layerManager = device->layerManager;

	Collider* c0 = (Collider*)s0->userData;
	Collider* c1 = (Collider*)s1->userData;

	// 각 콜라이더의 레이어 비트입니다.
	PxU32 layer0 = filterData0.word0;
	PxU32 layer1 = filterData1.word0;

	// 각 콜라이더의 충돌 가능한 비트들입니다.
	PxU32 collisionable0 = filterData0.word1 & layerManager->GetCollisionBits(c0->GetLayerIndex());
	PxU32 collisionable1 = filterData1.word1 & layerManager->GetCollisionBits(c1->GetLayerIndex());

	// 두 콜라이더의 충돌 가능성입니다.
	PxU32 collision = (layer0 & collisionable1) && (layer1 & collisionable0);

	if (!collision)
	{
		return PxFilterFlag::eSUPPRESS;
	}

	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}

	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	return PxFilterFlag::eDEFAULT;
}

void PhysicsFilterShader::pairLost(
	PxU32 pairID, 
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, 
	bool objectRemoved)
{
}

bool PhysicsFilterShader::statusChange(PxU32& pairID, PxPairFlags& pairFlags, PxFilterFlags& filterFlags)
{
	return false;
}

PxFilterFlags PhysicsFilterShader::PxSimulationFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, 
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	// pairFound 를 호출합니다.
	return PxFilterFlag::eCALLBACK;
}
