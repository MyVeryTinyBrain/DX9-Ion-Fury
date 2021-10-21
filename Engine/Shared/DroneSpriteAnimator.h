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

public:

	void SetAngle(float angle);

	void PlayIdle();

	void PlayShoot();

	void PlayMove(DIR_DRONE edir);

	void PlayMove();

	void PlayMoveShoot();

	void PlayExplosion();

	void PlaySmoke();

	bool IsPlayingIdle() const;

	bool IsPlayingShoot() const;

	bool IsPlayingMove() const;

	bool IsPlayingMoveShoot() const;

	bool IsPlayingExplosion() const;

	bool IsPlayingSmoke() const;

	SpriteAnimation* GetIdle() const;

	SpriteAnimation* GetMove() const;

	SpriteAnimation* GetShoot() const;
	
	SpriteAnimation* GetExplosion() const;

	SpriteAnimation* GetSmoke() const;

private:

	void ChangeUVDirection();

	void ResetUVDirection();

private:

	SpriteAnimation* m_idle;

	SpriteAnimation* m_shoot[(unsigned int)DIR_DRONE::MAX];

	SpriteAnimation* m_move[(unsigned int)DIR_DRONE::MAX];

	SpriteAnimation* m_moveShoot[(unsigned int)DIR_DRONE::MAX];

	SpriteAnimation* m_explosion;

	SpriteAnimation* m_smoke;

	float m_angle = 0.f;
};
