#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class BowAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void PlayIdle();

	void PlayShoot();

	void PlayReload();

public:

	bool IsPlayingIdle() const;

	bool IsPlayingShoot() const;

	bool IsPlayingReload() const;

	bool IsPlayingPullString() const;

private:

	SpriteAnimation* m_beginIdle;

	SpriteAnimation* m_idle;

	SpriteAnimation* m_beginShoot;

	SpriteAnimation* m_shootRecoil;

	SpriteAnimation* m_pullString;

	SpriteAnimation* m_reload;

public:

	Delegate<void()> OnReloaded;

	Delegate<void()> OnShoot;
};

