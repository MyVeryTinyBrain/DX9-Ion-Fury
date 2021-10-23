#pragma once

class ObjectCarBlue : public Component
{
	OverrideComponentFunction(Awake);

	class Cube* m_cube = nullptr;
};

