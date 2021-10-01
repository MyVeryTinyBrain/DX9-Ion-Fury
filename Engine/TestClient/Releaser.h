#pragma once

class Releaser : public Component
{
	OverrideComponentFunction(Update);

public:

	Ref<UserMesh> m_target = nullptr;
};

