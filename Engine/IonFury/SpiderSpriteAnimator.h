#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class SpiderSpriteAnimator :  public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd() override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;



private:

	SpriteAnimation* m_idle;


};

