#pragma once

class WarmechSpriteAnimator;

class WarmechHit : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

private:
	WarmechSpriteAnimator* m_animator = nullptr;

	GameObject* m_rendererObj = nullptr;

	float m_animationtime = 0;

	float m_moveSpeed = 0.f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	float m_radius = 0.5f;

	float m_selfDestroyCounter = 5.0f;

	UserMeshRenderer* m_debugRenderer = nullptr;

	bool m_initialdir = true;

	Vec3 forward;
};

