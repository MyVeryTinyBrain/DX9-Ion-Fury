#pragma once

class CamController : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	void Func(const wstring& msg);

	void Func2(const wstring& msg);

private:

	void MoveMouseToCenterPos();

	POINT GetMousePointInClient() const;

	Delegate<void(const wstring&)> OnSpace;
};

