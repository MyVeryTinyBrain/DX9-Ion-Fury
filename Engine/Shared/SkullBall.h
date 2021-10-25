#pragma once

class SkullBall : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(Start);

	OverrideComponentFunction(LateUpdate);

public:

	void SetVelocity(const Vec3& value);

	const Vec3& GetVelocity() const;

	__declspec(property(get = GetVelocity, put = SetVelocity)) const Vec3& velocity;

private:

	Collider* TriggerCheck();

	void OnTrigger(Collider* collider);

	void MakeExplosionEffect();

private:

	GameObject* m_root = nullptr;

	UserMeshBillboardRenderer* m_renderer = nullptr;

	float m_triggerRadius = 0.3f;

	UserMeshRenderer* m_debugRenderer = nullptr;

	Vec3 m_velocity = Vec3::zero();
};

