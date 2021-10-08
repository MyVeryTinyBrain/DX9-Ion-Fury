#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class RightHandAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	virtual void OnAnimationEnd() override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void PlayShoot();

private:

	SpriteAnimation* m_default = nullptr;

	SpriteAnimation* m_shoot = nullptr;
};

