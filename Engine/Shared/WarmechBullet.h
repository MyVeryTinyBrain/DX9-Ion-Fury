#pragma once

class WarmechSpriteAnimator;

class WarmechBullet : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);


private:

	WarmechSpriteAnimator* m_animator = nullptr;

	GameObject* m_rendererObj = nullptr;

	float m_animationtime = 0;

	float m_moveSpeed = 0.f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	Rigidbody* m_body = nullptr;

	float m_radius = 0.5f;

	float m_selfDestroyCounter = 5.0f;

	UserMeshRenderer* m_debugRenderer = nullptr;

	bool m_initialdir = true;

	Vec3 forward;

	bool m_hitCheck = false;

};

