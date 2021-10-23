#pragma once

class WarmechSpriteAnimator;

class WarmechExplosion : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(OnDestroy);

	void OnCollisionEnter(const CollisionEnter& collider);

private:
	WarmechSpriteAnimator* m_animator = nullptr;

	QuadUserMesh* m_quad = nullptr;

	Material* m_material = nullptr;

	float m_animationTime = 0.f;

	BoxCollider* m_collider = nullptr;

	GameObject* m_colliderObj = nullptr;
};

