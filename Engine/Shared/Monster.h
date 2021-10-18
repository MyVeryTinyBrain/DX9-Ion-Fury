#pragma once

enum class MonsterDamageType
{
	Zizizik,
	Bullet,
	Explosion,
};

struct DamageParameters
{
	// 몬스터가 피격당한 콜라이더입니다.
	Collider* monsterHitCollider = nullptr;

	// 공격의 형태입니다.
	MonsterDamageType damageType = MonsterDamageType::Bullet;

	// 몬스터에 적용되어야 할 데미지입니다.
	float damage = 0;

	// 몬스터의 강체에 적용되어야 할 힘입니다.
	Vec3 force = Vec3::zero();

	// 몬스터의 콜라이더에 적중한 좌표가 포함되었음을 알리는 플래그입니다.
	bool includeMonsterHitWorldPoint = false;

	// 공격이 몬스터의 콜라이더에 적중한 좌표입니다.
	Vec3 monsterHitWorldPoint = Vec3::zero();

	// 공격이 진행되는 방향이 포함되었음을 알리는 플래그입니다.
	bool includeDamageDirection = false;

	// 공격이 진행되는 방향벡터입니다.
	Vec3 damageDirection = Vec3::zero();

	// 공격이 시작된 좌표가 포함되었음을 알리는 플래그입니다.
	bool includeAttackBeginPoint = false;

	// 공격이 시작된 좌표입니다.
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

