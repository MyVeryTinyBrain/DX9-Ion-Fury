#pragma once

class Stalking : public Component
{
	OverrideComponentFunction(Update);

public:

	Ref<Transform> m_target;
};

