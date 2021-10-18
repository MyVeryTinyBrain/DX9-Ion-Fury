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

	void PlayMove(DIR_DECACONE edir);

	void PlayShoot();

	void PlayExplosion();

	void PlaySmoke();

	bool IsPlayingMove() const;

	bool IsPlayingShoot() const;

	bool IsPlayingExplosion() const;

	bool IsPlayingSmoke() const;

	SpriteAnimation* GetMove() const;

	SpriteAnimation* GetShoot() const;

	SpriteAnimation* GetExplosion() const;

	SpriteAnimation* GetSmoke() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_Attack;	//공격할때

	SpriteAnimation* m_move[(unsigned int)DIR_DECACONE::MAX]; //움직일때

	SpriteAnimation* m_zizizik[(unsigned int)DIR_DECACONE::MAX]; //지지직

	SpriteAnimation* m_dead;	//죽을때

	SpriteAnimation* m_smoke;	//이펙트

	float m_angle = 0.f;
};

