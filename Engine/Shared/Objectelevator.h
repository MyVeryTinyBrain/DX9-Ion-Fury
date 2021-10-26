#pragma once

#include "IDontDeactive.h"
#include "IUsable.h"

class Objectelevator :  public Component, public IUsable, public IDontDeactive
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	virtual void OnDisable() override;

public:

	void SetGoUpElevator();

	void SetGoDownElevator();

	bool GetUpElevator();

	bool GetDownElevator();

	void SetFloor(int _floor);

	int GetCurrentFloor();

	__declspec(property(get = GetUpElevator, put = SetGoUpElevator)) bool ElevatorGoUp;

	__declspec(property(get = GetDownElevator, put = SetGoDownElevator)) bool ElevatorGoDown;

	__declspec(property(get = GetCurrentFloor, put = SetFloor)) int Floor;


private:
	void ElevatorDoorControl();

private:

	GameObject* m_root = nullptr;

	GameObject* Upbutton = nullptr;

	GameObject* Downbutton = nullptr;

	GameObject* m_leftdoor = nullptr;

	GameObject* m_rightdoor = nullptr;

	GameObject* m_ground = nullptr;

	GameObject* m_B1button = nullptr;

	bool m_1Floor= true;

	bool m_2Floor = false;

	bool MoveElevator = false;

	bool GoDownElevator = false;

	int m_Floor = 0;

	bool opendoor = false;
	bool closedoor = false;





	Vec3  leftfirstlocalpositon;
	Vec3  rightfirstlocalpositon;
	float closedt = 0.f;

	// IUsable을(를) 통해 상속됨
	virtual void OnUse(bool valid) override;
};

