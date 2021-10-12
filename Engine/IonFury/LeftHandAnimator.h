#pragma once

#include "SpriteAnimator.h"

class LeftHandAnimator : public SpriteAnimator
{
	virtual void OnAnimationEnd(const SpriteAnimation* current) override;
	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;
	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;
};

