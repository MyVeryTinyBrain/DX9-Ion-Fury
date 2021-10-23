#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;


class WendigoSpriteAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;
	
	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;
	
	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_WENDIGO { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	enum class ATTACK_WENDIGO { Swing , Jump, Max };


public:

	void SetAngle(float angle);

	void PlayIdle();

	void PlayWalk();

	void PlayDamage();

	void PlayAttack(ATTACK_WENDIGO type);

	void PlayJump();

	void PlaySwing();

	void PlayDie();

	bool IsPlayingIdle() const;

	bool IsPlayingWalk() const;

	bool IsPlayingJump() const;

	bool IsPlayingAttack() const;

	bool IsPlayingDie() const;

	bool IsPlayingDamage() const;

	SpriteAnimation* GetIdle() const;

	SpriteAnimation* GetWalk() const;

	SpriteAnimation* GetAttack(ATTACK_WENDIGO type) const;

	SpriteAnimation* GetDie() const;

	SpriteAnimation* GetDamage() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_idle;

	SpriteAnimation* m_walk[(unsigned int)DIR_WENDIGO::MAX];

	SpriteAnimation* m_attack[(unsigned int)ATTACK_WENDIGO::Max];

	SpriteAnimation* m_die;

	SpriteAnimation* m_damage;

	float m_angle = 0.f;

public:

	Delegate<void()> OnPlayedJump;

	Delegate<void()> OnPlayedSwing;

	Delegate<void()> OnPlayedAttack;

	Delegate<void()> OnPlayedDie;
};

