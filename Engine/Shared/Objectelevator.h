#pragma once

#include "IDontDeactive.h"
#include "IUsable.h"

class Objectelevator :  public Component, public IUsable, IDontDeactive
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

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

	GameObject* rootleft = nullptr;

	GameObject* rootright = nullptr;

	GameObject* m_leftdoor = nullptr;

	GameObject* m_rightdoor = nullptr;

	GameObject* m_ground = nullptr;

	GameObject* m_B1button = nullptr;

	GameObject* m_1Floorbutton = nullptr;

	GameObject* m_2Floorbutton = nullptr;

	bool GoUpElevator = false;

	bool GoDownElevator = false;

	int m_Floor = 0;

	bool opendoor = false;
	bool closedoor = false;


	Vec3  leftfirstlocalpositon;
	Vec3  rightfirstlocalpositon;


public:
	// IUsable��(��) ���� ��ӵ�
	virtual void OnUse() override;
};

