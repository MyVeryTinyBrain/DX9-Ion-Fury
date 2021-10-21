#pragma once

class DeaconSpriteAnimator;

class DeaconflyEffect : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

private:
	DeaconSpriteAnimator* m_animator = nullptr;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	float m_animationTime = 0.f;

	float m_scail = 3.f;

	float scailminusTime = 0.f;
};

