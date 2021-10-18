#pragma once

class WarmechSpriteAnimator;

class WarmechMissile : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

private:

	WarmechSpriteAnimator* m_animator = nullptr;

	GameObject* m_rendererObj = nullptr;

	Rigidbody* m_body = nullptr;

	float m_moveSpeed = 0.f;

	float m_radius = 0.5f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	UserMeshRenderer* m_debugRenderer = nullptr;

	bool m_initialdir = true;

	Vec3 forward;

};

