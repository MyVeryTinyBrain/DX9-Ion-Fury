#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class SkullAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void SetAngle(float angle);

	void PlayIdle();

	void PlayWalk();

	void PlayAttack();

	void PlayFly();

	void PlayLand();

	void PlayDie();

	bool IsPlayingIdle() const;

	bool IsPlayingWalk() const;

	bool IsPlayingAttack() const;

	bool IsPlayingFlyAnimations() const;

	bool IsPlayingBeginFly() const;

	bool IsPlayingFly() const;

	bool IsPlayingLand() const;

	bool IsPlayingDie() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	enum class DIR { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	SpriteAnimation* m_idle[(int)DIR::MAX];

	SpriteAnimation* m_walk[(int)DIR::MAX];

	SpriteAnimation* m_attack;

	SpriteAnimation* m_beginFly;

	SpriteAnimation* m_fly;

	SpriteAnimation* m_land;

	SpriteAnimation* m_die;

	float m_angle = 0;

public:

	Delegate<void()> OnPlayedFly;

	Delegate<void()> OnPlayedLand;

	Delegate<void()> OnPlayedAttack;

	Delegate<void()> OnPlayedDie;
};

