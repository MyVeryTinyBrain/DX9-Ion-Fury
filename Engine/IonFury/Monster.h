#pragma once

enum class MonsterDamageType
{
	Zizizik,
	Bullet,
	Explosion,
};

class Monster : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(FixedUpdate);

	OverrideComponentFunction(Update);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

protected:

	virtual Collider* InitializeCollider(GameObject* colliderObj) = 0;

	virtual void OnDamage(Collider* collider, MonsterDamageType damageType, float& damage, Vec3& force) = 0;

	virtual void OnDead(bool& dead, MonsterDamageType damageType) = 0;

public:

	Vec3 ToSlopeVelocity(const Vec3& velocity, float rayLength = FLT_MAX) const;

	void TakeDamage(Collider* collider, MonsterDamageType damageType, float damage, Vec3 force = Vec3::zero());

	float AngleToPlayer() const;

	float AngleToPlayerWithSign() const;

public:

	float GetHP() const;

	void SetHP(float value);

	float GetMoveSpeed() const;

	void SetMoveSpeed(float value);

	__declspec(property(get = GetHP, put = SetHP)) float hp;

	__declspec(property(get = GetMoveSpeed, put = SetMoveSpeed)) float moveSpeed;

private:

	void DamageEffectProcessing();

protected:

	const float DAMAGE_EFFECT_DURATION = 0.1f;

	Rigidbody* m_body = nullptr;

	GameObject* m_colliderObj = nullptr;

	Collider* m_collider = nullptr;

	float m_hp = 1;

	float m_moveSpeed = 1.0f;

	float m_damageEffectCounter = 0.0f;

	Color m_damageEffectColor = Color::red();

	Material* m_material = nullptr;

	GameObject* m_rendererObj = nullptr;

	GameObject* m_rendererChildObj = nullptr;

	UserMeshBillboardRenderer* m_renderer = nullptr;

	QuadUserMesh* m_quad = nullptr;

	bool m_isDead = false;

	Color m_defaultEmissive = Color::black();

};

