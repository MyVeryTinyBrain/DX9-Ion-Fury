#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class MutantSpriteAnimator :   public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_MUTANT { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	enum class DIE_MUTANT { DIE_HEADSHOT, DIE_BODYSHOT, DIE_EXPLOSION, MAX };
public:

	void SetAngle(float angle);

	void PlayCreate();

	void PlayWalk();

	void PlayShoot();

	void PlayMutantPoison();

	void PlayDie(DIE_MUTANT type);

	bool IsPlayingWalk() const;

	bool IsPlayingShoot() const;

	bool IsPlayingMutantPoison() const;

	bool IsPlayingDie() const;

	bool IsPlayingCreate() const;


	SpriteAnimation* GetDie(DIE_MUTANT type) const;

	SpriteAnimation* GetWalk() const;

	SpriteAnimation* GetCreate() const;

	SpriteAnimation* GetMutantPoison() const;


private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_create;

	SpriteAnimation* m_walk;

	SpriteAnimation* m_shoot;

	SpriteAnimation* m_die[(unsigned int)DIE_MUTANT::MAX];

	SpriteAnimation* m_MutantPoison;

	float m_angle = 0.f;

public:

	Delegate<void()> OnDeadAnimated;
};

