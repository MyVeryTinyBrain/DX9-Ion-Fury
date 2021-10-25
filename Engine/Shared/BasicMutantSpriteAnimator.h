#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class BasicMutantSpriteAnimator :   public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_BasicMutant { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	enum class DIE_BasicMutant { DIE_HEADSHOT, DIE_EXPLOSION, MAX };
public:

	void SetAngle(float angle);

	void PlayCreate();

	void PlayWalk();

	void PlayAttack();


	void PlayDie(DIE_BasicMutant type);

	bool IsPlayingWalk() const;

	bool IsPlayingAttack() const;


	bool IsPlayingDie() const;

	bool IsPlayingCreate() const;


	SpriteAnimation* GetDie(DIE_BasicMutant type) const;

	SpriteAnimation* GetWalk() const;

	SpriteAnimation* GetCreate() const;

	SpriteAnimation* GetAttack() const;



private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_create;

	SpriteAnimation* m_walk;

	SpriteAnimation* m_Attack;

	SpriteAnimation* m_die[(unsigned int)DIE_BasicMutant::MAX];


	float m_angle = 0.f;

public:

	Delegate<void()> OnDeadAnimated;

	Delegate<void()> OnCreateAnumated;

};

