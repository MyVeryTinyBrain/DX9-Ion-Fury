#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class SpiderSpriteAnimator :  public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd() override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_SPIDER { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX};

public:

	void PlayWalk();

	bool IsPlayingWalk() const;

private:

	SpriteAnimation* m_walk[(unsigned int)DIR_SPIDER::MAX];


};

