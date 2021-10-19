#pragma once

class Arrow : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(OnDestroy);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	void OnCollisionEnter(const CollisionEnter& collider);

public:

	Rigidbody* GetRigidbody() const;

	__declspec(property(get = GetRigidbody)) Rigidbody* rigidbody;

private:

	void RemoveBodyAndCollider();

	void RemoveRenderer();

private:

	GameObject* m_rendererObj = nullptr;

	GameObject* m_colliderObj = nullptr;

	Rigidbody* m_rigidbody = nullptr;

	BoxCollider* m_collider = nullptr;

	UserMeshRenderer* m_renderer = nullptr;

	int m_damage = 30;

	float m_selfDestroyCounter = 10.0f;

	UserMeshRenderer* m_colliderDebugRenderer = nullptr;

	Vec3 m_beginPoint;

	class TrailRenderer* m_trailRenderer = nullptr;

	bool m_hitOnTerrain = false;
};

