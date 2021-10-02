#pragma once

#include "Component.h"

class SimpleBody : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(EndPhysicsSimulate);

	PxRigidDynamic* m_body;
};

