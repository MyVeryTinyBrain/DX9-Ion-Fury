#pragma once

class Rotater : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnWake);

private:

	float m_value;

	float m_dtScale;
};

