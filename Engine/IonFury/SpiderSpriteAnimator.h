#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class SpiderSpriteAnimator :  public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_SPIDER { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX};

	enum class DIE_SPIDER { DIE_HEADSHOT, DIE_GENERIC, MAX};


public:
	
	void SetAngle(float angle);

	void PlayIdle();

	void PlayWalk();

	void PlayJump();

	void PlayDamage();

	void PlayDie(DIE_SPIDER type);

	bool IsPlayingIdle() const;

	bool IsPlayingWalk() const;

	bool IsPlayingJump() const;

	bool IsPlayingDamage() const;

	bool IsPlayingDie() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_Idle;

	SpriteAnimation* m_walk[(unsigned int)DIR_SPIDER::MAX];

	SpriteAnimation* m_jump[(unsigned int)DIR_SPIDER::MAX];

	SpriteAnimation* m_damage;

	SpriteAnimation* m_die[(unsigned int)DIE_SPIDER::MAX];

	float m_angle = 0.f;
};

