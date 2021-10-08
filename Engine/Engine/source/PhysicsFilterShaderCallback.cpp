#include "EngineBase.h"
#include "PhysicsFilterShaderCallback.h"
#include "PhysicsDevice.h"
#include "LayerManager.h"
#include "Collider.h"

using namespace PhysicsFilterShaderCallbackFilters;

PxFilterFlags PhysicsFilterShaderCallback::pairFound(
	PxU32 pairID, 
	PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor* a0, const PxShape* s0, 
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor* a1, const PxShape* s1, 
	PxPairFlags& pairFlags)
{
	// Ʈ���Ÿ� ������ �浹���� ó���մϴ�.

	auto device = PhysicsDevice::GetInstance();
	auto layerManager = device->layerManager;

	Collider* c0 = (Collider*)s0->userData;
	Collider* c1 = (Collider*)s1->userData;

	// �� �ݶ��̴��� ���̾� ��Ʈ�Դϴ�.
	PxU32 layer0 = filterData0.word0;
	PxU32 layer1 = filterData1.word0;

	// �� �ݶ��̴��� �浹 ������ ��Ʈ���Դϴ�.
	PxU32 collisionable0 = filterData0.word1 & layerManager->GetCollisionBits(c0->GetLayerIndex());
	PxU32 collisionable1 = filterData1.word1 & layerManager->GetCollisionBits(c1->GetLayerIndex());

	// �� �ݶ��̴��� �浹 ���ɼ��Դϴ�.
	PxU32 collision = (layer0 & collisionable1) && (layer1 & collisionable0);

	if (!collision)
	{
		return PxFilterFlag::eSUPPRESS;
	}

	pairFlags = eContactFlags;
	return PxFilterFlag::eDEFAULT;
}

PxFilterFlags PhysicsFilterShaderCallback::PxSimulationFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, 
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		// Ʈ���Ÿ� ó������ �ʽ��ϴ�.
		return PxFilterFlag::eSUPPRESS;

		// pairFlags = eTriggerFlags;
		// return PxFilterFlag::eDEFAULT;
	}

	// pairFound �� ȣ���ϴ� �÷����Դϴ�.
	return PxFilterFlag::eCALLBACK;
}
