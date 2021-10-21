#pragma once

class DroneSpriteAnimator;

class DroneSmoke : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);



private:
	DroneSpriteAnimator* m_animator = nullptr;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	float m_animationTime = 0.f;
};

