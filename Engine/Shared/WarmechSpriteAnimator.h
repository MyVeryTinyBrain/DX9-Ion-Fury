#pragma once

#include "SpriteAnimator.h"


enum class SPRITE_WARMECH { Idle, Walk, WalkIdle, Shoot, Missile, Bullet, MissileBullet, Damage, Explosion, Max };

class WarmechSpriteAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_WARMECH { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

public:

	void SetAngle(float angle);

	void PlayIdle();

	void PlayWalk();

	void PlayWalkIdle();

	void PlayShoot();

	void PlayMissile();

	void PlayBullet();

	void PlayMissileBullet();

	void PlayDamage();

	void PlayExplosion();

	bool IsPlayingIdle() const;

	bool IsPlayingWalk() const;

	bool IsPlayingWalkIdle() const;

	bool IsPlayingShoot() const;

	bool IsPlayingMissile() const;

	bool IsPlayingBullet() const;

	bool IsPlayingMissileBullet() const;

	bool IsPlayingDamage() const;

	bool IsPlayingExplosion() const;

	SpriteAnimation* GetSpriteAnimation(SPRITE_WARMECH Spritetype) const;


private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_idle[(unsigned int)DIR_WARMECH::MAX];

	SpriteAnimation* m_walk[(unsigned int)DIR_WARMECH::MAX];

	SpriteAnimation* m_walkIdle;

	SpriteAnimation* m_shoot;

	SpriteAnimation* m_missile;

	SpriteAnimation* m_bullet;

	SpriteAnimation* m_missileBullet;

	SpriteAnimation* m_damage;

	SpriteAnimation* m_explosion;

	float m_angle = 0.f;

};

