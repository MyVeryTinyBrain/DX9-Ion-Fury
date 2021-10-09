#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class GunnerSpriteAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd() override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR { FRONT, SIDE, BACK, MAX };

	enum class DIE { DIE_HEADSHOT, DIE_BODYSHOT, DIE_EXPLOSION, MAX };

	enum class DAMAGE { DAMAGE_ZIZIZIK, DAMAGE_GENERIC, MAX };

public:

	void PlayIdle();

	void PlayWalk(DIR direction);

	SpriteAnimation* m_idle;

	SpriteAnimation* m_walk[(unsigned int)DIR::MAX];

	SpriteAnimation* m_shoot;

	SpriteAnimation* m_die[(unsigned int)DIE::MAX];

	SpriteAnimation* m_damage[(unsigned int)DAMAGE::MAX];

};

