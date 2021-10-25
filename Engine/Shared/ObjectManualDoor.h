#pragma once

#include "ObjectAutoDoor.h"

class ObjectManualDoor : public ObjectAutoDoor
{
	OverrideComponentFunction(Awake);
};

