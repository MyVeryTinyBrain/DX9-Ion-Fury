#pragma once

class IUsable
{
public:

	virtual void OnUse(bool valid) = 0;

	virtual void OnDisable() {};
};

