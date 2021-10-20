#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class GunnerBaseAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	enum class DIE { DIE_HEADSHOT, DIE_BODYSHOT, DIE_EXPLOSION, MAX };

	enum class DAMAGE { DAMAGE_ZIZIZIK, DAMAGE_GENERIC, MAX };

protected:

	virtual void InitAnimations() = 0;

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

protected:

	SpriteAnimation* m_idle[(unsigned int)DIR::MAX];

	SpriteAnimation* m_walk[(unsigned int)DIR::MAX];

	SpriteAnimation* m_shoot;

	SpriteAnimation* m_die[(unsigned int)DIE::MAX];

	SpriteAnimation* m_damage[(unsigned int)DAMAGE::MAX];

	float m_angle = 0;

public:

	Delegate<void()> OnDeadAnimated;
};

