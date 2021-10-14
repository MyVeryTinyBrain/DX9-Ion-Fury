#pragma once

class GranadeTrail : public Component
{
	OverrideComponentFunction(Update);

	void MakeTrailEffectOnce();

	float m_delay = 0.01f;

	float m_singleEffectDuration = 0.5f;

	float m_singleEffectScale = 0.25f;

	float m_makeEffectCounter = m_delay;
};

