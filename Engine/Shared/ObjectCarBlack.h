#pragma once

class ObjectCarBlack : public Component
{
	OverrideComponentFunction(Awake);

	class Cube* m_cube = nullptr;
};

