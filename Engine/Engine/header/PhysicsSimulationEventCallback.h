#pragma once

#include "PhysicsCallbackTypes.h"

class PhysicsSimulationEventCallback : public PxSimulationEventCallback
{
	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override {}

	virtual void onWake(PxActor** actors, PxU32 count) override {}

	virtual void onSleep(PxActor** actors, PxU32 count) override {}

	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;

	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override {}

	virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override {}

public:

	void ClearBuffers();

	void ExecuteNotify();

private:

	std::vector<CollisionEnter> m_enterings;

	std::vector<CollisionExit> m_exitings;

	std::vector<CollisionStay> m_stayings;
};

