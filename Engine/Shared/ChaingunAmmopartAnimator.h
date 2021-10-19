#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class ChaingunAmmopartAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void PlayIdle();

	void PlayAnim();

private:

	SpriteAnimation* m_default;

	SpriteAnimation* m_anim;
};

