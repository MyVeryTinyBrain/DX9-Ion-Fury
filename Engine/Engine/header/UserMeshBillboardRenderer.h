#pragma once

#include "UserMeshRenderer.h"

class UserMeshBillboardRenderer : public UserMeshRenderer
{
	OverrideComponentFunction(Render);
};

