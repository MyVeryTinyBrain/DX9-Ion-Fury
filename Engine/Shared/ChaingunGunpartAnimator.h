#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class ChaingunGunpartAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	OverrideComponentFunction(AnimationUpdate);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

private:

	SpriteAnimation* m_default;

	unsigned int m_beforeFrame = 0;

public:

	Delegate<void()> OnRotatedBarrel;
};

