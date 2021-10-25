#pragma once

#include "Trigger.h"

class BossTrigger : public Trigger
{
	OverrideComponentFunction(Start);

	virtual void OnUse();

	class ObjectAutoDoor* m_door = nullptr;
};

