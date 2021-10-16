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

public:

	void SetAngle(float angle);

	void PlayIdle();

	void PlayShoot();

	void PlayMove(DIR_DECACONE edir);

	void PlayMove();

	void PlayMoveShoot();

	void PlayExplosion();

	void PlaySmoke();

	bool IsPlayingIdle() const;

	bool IsPlayingShoot() const;

	bool IsPlayingMove() const;

	bool IsPlayingMoveShoot() const;

	bool IsPlayingExplosion() const;

	bool IsPlayingSmoke() const;

	SpriteAnimation* GetIdle() const;

	SpriteAnimation* GetMove() const;

	SpriteAnimation* GetShoot() const;

	SpriteAnimation* GetExplosion() const;

	SpriteAnimation* GetSmoke() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_idle[(unsigned int)DIR_DECACONE::MAX]; //기본

	SpriteAnimation* m_Attack[(unsigned int)DIR_DECACONE::MAX];	//공격할때

	SpriteAnimation* m_move[(unsigned int)DIR_DECACONE::MAX]; //움직일때

	SpriteAnimation* m_zizizik[(unsigned int)DIR_DECACONE::MAX]; //지지직

	SpriteAnimation* m_explosion;	//죽을때

	SpriteAnimation* m_smoke;	//이펙트

	float m_angle = 0.f;
};

