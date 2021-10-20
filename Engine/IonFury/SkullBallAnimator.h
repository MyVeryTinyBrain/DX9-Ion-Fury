#pragma once

#include <SpriteAnimator.h>

class SkullBallAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);
	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;
	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;
	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	class SpriteAnimation* m_animation = nullptr;
};

