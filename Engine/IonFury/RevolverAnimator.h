#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class RevolverAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void PlayShoot();

	void PlayReload();

public:

	bool IsPlayingIdle() const;

	bool IsPlayingShoot() const;

	bool IsPlayingReload() const;

	bool IsPlayingReloadPutin() const;

private:

	SpriteAnimation* m_default = nullptr;

	SpriteAnimation* m_shoot = nullptr;

	SpriteAnimation* m_beginReload = nullptr;

	SpriteAnimation* m_reloadingPutin = nullptr;

	SpriteAnimation* m_reloadingPullout = nullptr;

	SpriteAnimation* m_endReload = nullptr;

public:

	Delegate<void()> OnReloaded;
};

