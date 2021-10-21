#include "shared_stdafx.h"
#include "ObjectManualDoor.h"

void ObjectManualDoor::Awake()
{
	ObjectAutoDoor::Awake();

	autoOpen = false;
}
