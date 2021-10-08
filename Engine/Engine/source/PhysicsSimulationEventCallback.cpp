#include "EngineBase.h"
#include "PhysicsSimulationEventCallback.h"
#include "Collider.h"
#include "Rigidbody.h"

void PhysicsSimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	if (pairs->events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
	{
		CollisionEnter enterB2A(pairs, false);
		CollisionEnter enterA2B(pairs, true);
		m_enterings.push_back(std::move(enterB2A));
		m_enterings.push_back(std::move(enterA2B));
	}
	else if (pairs->events & PxPairFlag::eNOTIFY_TOUCH_LOST)
	{
		CollisionExit exitAB(pairs->shapes[0], pairs->shapes[1]);
		CollisionExit exitBA(pairs->shapes[1], pairs->shapes[0]);
		m_exitings.push_back(std::move(exitAB));
		m_exitings.push_back(std::move(exitBA));
	}
	else if (pairs->events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
	{
		CollisionStay stayB2A(pairs, false);
		CollisionStay stayA2B(pairs, true);
		m_stayings.push_back(std::move(stayB2A));
		m_stayings.push_back(std::move(stayA2B));
	}
}

void PhysicsSimulationEventCallback::ClearBuffers()
{
	m_enterings.clear();
	m_exitings.clear();
	m_stayings.clear();
}

void PhysicsSimulationEventCallback::ExecuteNotify()
{
	for (auto& pair : m_enterings)
	{
		pair.toCollider->OnCollisionEnter(pair);
	}

	for (auto& pair : m_exitings)
	{
		pair.fromCollider->OnCollisionExit(pair);
	}

	for (auto& pair : m_stayings)
	{
		pair.toCollider->OnCollisionStay(pair);
	}

	ClearBuffers();
}
