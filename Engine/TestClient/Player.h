#pragma once

class Player : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

public:

	void SetArmLocalAngle(float angle);

private:

	GameObject* m_sphere;

	GameObject* m_leftArm1;

	GameObject* m_leftArm2;

	GameObject* m_rightArm1;

	GameObject* m_rightArm2;

	UserMeshRenderer* m_renderers[5];
};

