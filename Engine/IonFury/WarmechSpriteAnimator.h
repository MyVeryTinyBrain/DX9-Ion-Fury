#pragma once

#include "SpriteAnimator.h"

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

	void PlayShoot();

	void PlayMissile();

	void PlayBullet();

	void PlayMissileBullet();

	void PlayDamage();

	void PlayExplosion();

	bool IsPlayingIdle() const;

	bool IsPlayingWalk() const;

	bool IsPlayingShoot() const;

	bool IsPlayingMissile() const;

	bool IsPlayingBullet() const;

	bool IsPlayingMissileBullet() const;

	bool IsPlayingDamage() const;

	bool IsPlayingExplosion() const;

	SpriteAnimation* GetIdle() const;

	SpriteAnimation* GetWalk() const;

	SpriteAnimation* GetShoot() const;

	SpriteAnimation* GetMissile() const;

	SpriteAnimation* GetBullet() const;

	SpriteAnimation* GetMissileBullet() const;

	SpriteAnimation* GetDamage() const;

	SpriteAnimation* GetExplosion() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_idle[(unsigned int)DIR_WARMECH::MAX];

	SpriteAnimation* m_walk[(unsigned int)DIR_WARMECH::MAX];

	SpriteAnimation* m_shoot;

	SpriteAnimation* m_missile;

	SpriteAnimation* m_bullet;

	SpriteAnimation* m_missileBullet;

	SpriteAnimation* m_damage;

	SpriteAnimation* m_explosion;

	float m_angle = 0.f;

};

