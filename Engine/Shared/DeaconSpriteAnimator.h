#pragma once
#include "SpriteAnimator.h"

class DeaconSpriteAnimator :   public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_DECACONE{ FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	enum class DIE {DIE, MAX};

public:

	void SetAngle(float angle);

	void PlayMove(DIR_DECACONE edir);

	void PlayShoot();

	void PlayExplosion();

	void PlayDie();

	void PlayIdle();

	void PlayDamage();

	void PlaySmoke();

	bool IsPlayingMove() const;
	
	bool IsPlayingIdle() const;

	bool IsPlayingShoot() const;

	bool IsPlayingExplosion() const;

	bool IsPlayingSmoke() const;

	bool IsPlayingDamage() const;

	SpriteAnimation* GetMove() const;

	SpriteAnimation* GetIdle() const;

	SpriteAnimation* GetShoot() const;

	SpriteAnimation* GetExplosion() const;

	SpriteAnimation* GetSmoke() const;

	SpriteAnimation* GetDamage() const;


private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_Attack;	//�����Ҷ�

	SpriteAnimation* m_move[(unsigned int)DIR_DECACONE::MAX]; //�����϶�

	SpriteAnimation* m_zizizik[(unsigned int)DIR_DECACONE::MAX]; //������

	SpriteAnimation* m_dead;	//������

	SpriteAnimation* m_Idle;	//����Ʈ

	SpriteAnimation* m_damage;	//����Ʈ

	float m_angle = 0.f;

	SpriteAnimation* m_flyeffect;


public:

public:

	Delegate<void()> OnPlayedFly;

	Delegate<void()> OnPlayedLand;

	Delegate<void()> OnPlayedAttack;

	Delegate<void()> OnPlayedDie;
};

