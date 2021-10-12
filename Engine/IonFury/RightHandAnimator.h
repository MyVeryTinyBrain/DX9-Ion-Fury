#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class RightHandAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void PlayShoot();

private:

	SpriteAnimation* m_default = nullptr;

	SpriteAnimation* m_shoot = nullptr;
};

