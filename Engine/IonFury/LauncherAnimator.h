#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class LauncherAnimator : public SpriteAnimator
{
public:

	enum class Skin
	{
		Red, Yellow, Max
	};

private:

	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void SetSkin(Skin value);

	void PlayIdle();

	void PlayShoot();

	void PlayReload();

	void PlayChangeToRed();

	void PlayChangeToYellow();

	bool IsPlayingIdle() const;

	bool IsPlayingShoot() const;

	bool IsPlayingReload() const;

	bool IsPlayingSkinChange() const;

private:

	Skin m_skin = Skin::Red;

	SpriteAnimation* m_idle[(int)Skin::Max];

	SpriteAnimation* m_beginIdle[(int)Skin::Max];

	SpriteAnimation* m_shoot[(int)Skin::Max];

	SpriteAnimation* m_pullPump[(int)Skin::Max];

	SpriteAnimation* m_reload[(int)Skin::Max];

	SpriteAnimation* m_SkinChange[(int)Skin::Max];

public:

	Delegate<void()> OnReloaded;

	Delegate<void()> OnSkinChanged;
};

