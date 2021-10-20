#pragma once

class MutantSpriteAnimator;

class MutantPoison : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);


private:
	MutantSpriteAnimator* m_animator = nullptr;

	GameObject* m_rendererObj = nullptr;

	float m_animationtime = 0;

	float m_moveSpeed = 0.f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	float m_radius = 0.5f;

	float m_selfDestroyCounter = 3.0f;

	UserMeshRenderer* m_debugRenderer = nullptr;

	bool m_initialdir = true;

	Vec3 forward;
};
