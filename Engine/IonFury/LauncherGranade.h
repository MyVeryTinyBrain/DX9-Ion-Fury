#pragma once

class LauncherGranade : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	OverrideComponentFunction(Update);

	void OnCollisionEnter(const CollisionEnter& collider);

public:

	void Explosion();

	Rigidbody* GetRigidbody() const;

	__declspec(property(get = GetRigidbody)) Rigidbody* rigidbody;

private:

	GameObject* m_rendererObj = nullptr;

	GameObject* m_colliderObj = nullptr;

	GameObject* m_explosionDebugRendererObj = nullptr;

	Rigidbody* m_rigidbody = nullptr;

	SphereCollider* m_collider = nullptr;

	bool m_exploded = false;

	UserMeshBillboardRenderer* m_renderer = nullptr;

	int m_explosionDamage = 10;

	float m_explosionRadius = 1.5f;

	bool m_groundCollision = false;

	float m_selfExplosionCounter = 2.5f;

	float m_selfDestroyCounter = 30.0f;

	//UserMeshRenderer* m_colliderDebugRenderer = nullptr;

	//UserMeshRenderer* m_explosionDebugRenderer = nullptr;
};

