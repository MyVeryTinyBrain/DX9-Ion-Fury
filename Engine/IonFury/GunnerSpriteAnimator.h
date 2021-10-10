#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class GunnerSpriteAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd() override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	enum class DIE { DIE_HEADSHOT, DIE_BODYSHOT, DIE_EXPLOSION, MAX };

	enum class DAMAGE { DAMAGE_ZIZIZIK, DAMAGE_GENERIC, MAX };

public:

	void SetAngle(float angle);

	void PlayIdle();

	void PlayWalk();

	void PlayShoot();

	void PlayDie(DIE type);

	void PlayDamage(DAMAGE type);

	bool IsPlayingIdle() const;

	bool IsPlayingWalk() const;

	bool IsPlayingShoot() const;

	bool IsPlayingDie() const;

	bool IsPlayingDamage() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_idle[(unsigned int)DIR::MAX];

	SpriteAnimation* m_walk[(unsigned int)DIR::MAX];

	SpriteAnimation* m_shoot;

	SpriteAnimation* m_die[(unsigned int)DIE::MAX];

	SpriteAnimation* m_damage[(unsigned int)DAMAGE::MAX];

	float m_angle = 0;

};

