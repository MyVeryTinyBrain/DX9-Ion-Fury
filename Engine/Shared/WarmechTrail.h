#pragma once
class WarmechTrail : public Component
{
	OverrideComponentFunction(Update);

	void MakeTrailEffectOnce();

	float m_delay = 0.1f;

	float m_singleEffectDuration = 1.0f;

	float m_singleEffectScale = 0.15f;

	float m_makeEffectCounter = m_delay;
};

