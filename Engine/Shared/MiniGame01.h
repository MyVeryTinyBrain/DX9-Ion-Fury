#pragma once

class Monster;

class MiniGame01 : public Component
{
public:
	
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

private:

	GameObject*				m_CameraObj;

	std::vector<Monster*>	MonsterVec;
};

