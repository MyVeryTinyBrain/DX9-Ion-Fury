#pragma once

class BloodEffect : public Component
{
	OverrideComponentFunction(Awake);

private:

	class BillboardEffect* m_effect;
};

