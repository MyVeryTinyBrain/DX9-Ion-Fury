#include "EngineBase.h"
#include "PhysicsSimulationEventCallback.h"

void PhysicsSimulationEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
	cout << "onConstraintBreak" << endl;
}

void PhysicsSimulationEventCallback::onWake(PxActor** actors, PxU32 count)
{
	cout << "onWake" << endl;
}

void PhysicsSimulationEventCallback::onSleep(PxActor** actors, PxU32 count)
{
	cout << "onSleep" << endl;
}

void PhysicsSimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	cout << "onContact" << endl;
}

void PhysicsSimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	cout << "onTrigger" << endl;
}

void PhysicsSimulationEventCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
	cout << "onAdvance" << endl;
}
