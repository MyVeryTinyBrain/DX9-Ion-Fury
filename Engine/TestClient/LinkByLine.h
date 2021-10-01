#pragma once

class LinkByLine : public Component
{
	OverrideComponentFunction(Render);

	OverrideComponentFunction(OnWake);

	OverrideComponentFunction(OnSleep);

public:

	void SetTargetA(Ref<Transform> target);

	void SetTargetB(Ref<Transform> target);

private:

	Ref<Transform> m_targetA;

	Ref<Transform> m_targetB;
};

