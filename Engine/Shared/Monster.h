#pragma once

enum class MonsterDamageType
{
	Zizizik,
	Bullet,
	Explosion,
};

struct DamageParameters
{
	// ���Ͱ� �ǰݴ��� �ݶ��̴��Դϴ�.
	Collider* monsterHitCollider = nullptr;

	// ������ �����Դϴ�.
	MonsterDamageType damageType = MonsterDamageType::Bullet;

	// ���Ϳ� ����Ǿ�� �� �������Դϴ�.
	float damage = 0;

	// ������ ��ü�� ����Ǿ�� �� ���Դϴ�.
	Vec3 force = Vec3::zero();

	// ������ �ݶ��̴��� ������ ��ǥ�� ���ԵǾ����� �˸��� �÷����Դϴ�.
	bool includeMonsterHitWorldPoint = false;

	// ������ ������ �ݶ��̴��� ������ ��ǥ�Դϴ�.
	Vec3 monsterHitWorldPoint = Vec3::zero();

	// ������ ����Ǵ� ������ ���ԵǾ����� �˸��� �÷����Դϴ�.
	bool includeDamageDirection = false;

	// ������ ����Ǵ� ���⺤���Դϴ�.
	Vec3 damageDirection = Vec3::zero();

	// ������ ���۵� ��ǥ�� ���ԵǾ����� �˸��� �÷����Դϴ�.
	bool includeAttackBeginPoint = false;

	// ������ ���۵� ��ǥ�Դϴ�.
	Vec3 attackBeginPoint = Vec3::zero();
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

	virtual void OnDamage(DamageParameters& params) = 0;

	virtual void OnDead(bool& dead, DamageParameters& params) = 0;

public:

	Vec3 ToSlopeVelocity(const Vec3& velocity, float rayLength = FLT_MAX) const;

	void TakeDamage(const DamageParameters& params);

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

	UserMeshBillboardRenderer* CreateRenderer();

protected:

	const float DAMAGE_EFFECT_DURATION = 0.5f;

	Rigidbody* m_body = nullptr;

	Ref<Rigidbody> m_refBody;

	GameObject* m_colliderObj = nullptr;

	Collider* m_collider = nullptr;

	float m_hp = 1;

	float m_moveSpeed = 1.0f;

	float m_damageEffectCounter = 0.0f;

	Color m_damageEffectColor = Color::red();

	Material* m_material = nullptr;

	GameObject* m_rendererObj = nullptr;

	std::vector<Ref<UserMeshBillboardRenderer>> m_renderers;

	QuadUserMesh* m_quad = nullptr;

	bool m_isDead = false;

	Color m_defaultEmissive = Color::black();

};

