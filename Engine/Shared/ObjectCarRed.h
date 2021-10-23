#pragma once

class ObjectCarRed : public Component
{
	OverrideComponentFunction(Awake);

	class Cube* m_cube = nullptr;
};

