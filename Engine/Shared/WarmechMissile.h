#pragma once

class WarmechSpriteAnimator;

class WarmechMissile : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	void OnCollisionEnter(const CollisionEnter& collider);

public:

	void Explosion();

	void Rebound();


private:

	WarmechSpriteAnimator* m_animator = nullptr;

	GameObject* m_rendererObj = nullptr;

	Rigidbody* m_body = nullptr;

	GameObject* m_colliderObj = nullptr;

	SphereCollider* m_collider = nullptr;

	float m_moveSpeed = 0.f;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	UserMeshRenderer* m_debugRenderer = nullptr;

	bool m_initialdir = true;

	Vec3 forward;

	bool m_groundCollision = false;

	float m_selfExplosionCounter = 2.f;

	float m_selfDestroyCounter = 30.0f;

	bool m_rebound = true;

	float m_reboudcount = 1.f;

	bool m_hitCheck = false;

	float m_radius = 0.5f;
};

