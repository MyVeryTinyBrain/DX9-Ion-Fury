#pragma once

class CamController : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

private:

	void MoveMouseToCenterPos();

	POINT GetMousePointInClient() const;
};

