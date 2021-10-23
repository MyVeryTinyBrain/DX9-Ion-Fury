#pragma once

#include "SpriteAnimator.h"

class SpriteAnimation;

class ObjectRatAnimator : public SpriteAnimator
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(LateUpdate);

	OverrideComponentFunction(OnDestroy);

	virtual void OnAnimationEnd(const SpriteAnimation* current) override;

	virtual void OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

	virtual void OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next) override;

public:

	void SetAngle(float angle);

	void PlayIdle();

	void PlayWalk();

	bool IsPlayingIdle() const;

	bool IsPlayingWalk() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	enum class DIR { FRONT, FRONT_DIAGONAL, SIDE, BACK_DIAGONAL, BACK, MAX };

	float m_angle = 0;

	SpriteAnimation* m_idle[(int)DIR::MAX];

	SpriteAnimation* m_walk[(int)DIR::MAX];
};

