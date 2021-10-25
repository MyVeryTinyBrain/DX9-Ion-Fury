#pragma once

class WebSpriteAnimator;

class Web : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	void OnCollisionEnter(const CollisionEnter& collider);

private:

	WebSpriteAnimator* m_animator = nullptr;

	Rigidbody* m_body = nullptr;

	GameObject* m_rendererObj = nullptr;

	float m_animationtime = 0;

	float m_moveSpeed = 0.f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	BoxCollider* m_collider = nullptr;

	GameObject* m_colliderObj = nullptr;

	float m_deadtime = 0.f;
};

