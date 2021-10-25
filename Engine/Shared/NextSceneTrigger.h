#pragma once

#include "Trigger.h"

class NextSceneTrigger : public Trigger
{
	OverrideComponentFunction(LateUpdate);

	virtual void OnUse();

private:

	bool m_beginFade = false;

	bool m_endFade = false;
};

