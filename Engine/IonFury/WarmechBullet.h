#pragma once

class WarmechSpriteAnimator;

class WarmechBullet : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

private:

	WarmechSpriteAnimator* m_animator = nullptr;

	Rigidbody* m_body = nullptr;

	GameObject* m_rendererObj = nullptr;

	float m_animationtime = 0;

	float m_moveSpeed = 0.f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;
};

