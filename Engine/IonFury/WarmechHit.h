#pragma once

class WarmechSpriteAnimator;

class WarmechHit : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

private:
	WarmechSpriteAnimator* m_animator = nullptr;

	Rigidbody* m_body = nullptr;

	GameObject* m_rendererObj = nullptr;

	float m_moveSpeed = 0.f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	float m_selfDestroyCounter = 3.0f;

	bool m_ground = false;
};

