#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class SMGAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void PlayIdle();

	void PlayFire();

	void PlayReload();

	void PlayPutin();

	void PlayPullout();

public:

	bool IsPlayingIdle() const;

	bool IsPlayingFire() const;

	bool IsPlayingReload() const;

	bool IsPlayingPutin() const;

	bool IsPlayingPullout() const;

private:

	SpriteAnimation* m_beginIdle;

	SpriteAnimation* m_idle;

	SpriteAnimation* m_fire;

	SpriteAnimation* m_reload;

	SpriteAnimation* m_putin;

	SpriteAnimation* m_pullout;

public:

	Delegate<void()> OnReloaded;

	Delegate<void()> OnPlayedPutin;

	Delegate<void()> OnPlayPullout;
};

