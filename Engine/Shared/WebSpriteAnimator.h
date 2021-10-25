#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class WebSpriteAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void PlayWeb();

	bool IsPlayingWeb() const;

	SpriteAnimation* GetWeb() const;

private:

	SpriteAnimation* m_web;

	float m_angle = 0.f;
};

