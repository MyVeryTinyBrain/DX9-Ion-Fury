#pragma once

class ObjectGetItem : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);
private:

	int m_hitCount = 0;

};

