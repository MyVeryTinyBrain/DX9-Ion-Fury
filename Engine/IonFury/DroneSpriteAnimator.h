#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class DroneSpriteAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	enum class DIR_DRONE { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	

private:

	SpriteAnimation* m_idle[(unsigned int)DIR_DRONE::MAX];

	SpriteAnimation* m_shoot[(unsigned int)DIR_DRONE::MAX];

	SpriteAnimation* m_move[(unsigned int)DIR_DRONE::MAX];

	SpriteAnimation* m_moveShoot[(unsigned int)DIR_DRONE::MAX];

	float m_angle = 0.f;
};

