#include "shared_stdafx.h"
#include "GunnerBaseAnimator.h"
#include "SpriteAnimation.h"

void GunnerBaseAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(unsigned int)DIR::FRONT] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::FRONT]->isLoop = true;

	m_idle[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR::SIDE] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::SIDE]->isLoop = true;

	m_idle[(unsigned int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR::BACK] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::BACK]->isLoop = true;

	m_walk[(unsigned int)DIR::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT]->interval = 0.1f;
	m_walk[(unsigned int)DIR::FRONT]->isLoop = true;

	m_walk[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->interval = 0.1f;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->isLoop = true;

	m_walk[(unsigned int)DIR::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::SIDE]->interval = 0.1f;

	m_walk[(unsigned int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->interval = 0.1f;

	m_walk[(unsigned int)DIR::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::BACK]->interval = 0.1f;

	m_shoot = new SpriteAnimation;
	m_shoot->interval = 0.05f;

	m_die[(unsigned int)DIE::DIE_HEADSHOT] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->interval = 0.1f;

	m_die[(unsigned int)DIE::DIE_BODYSHOT] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->interval = 0.1f;

	m_die[(unsigned int)DIE::DIE_EXPLOSION] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->interval = 0.1f;

	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK] = new SpriteAnimation;
	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK]->interval = 0.3f;

	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC] = new SpriteAnimation;
	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC]->interval = 0.3f;

	InitAnimations();

	SetDefaultAnimation(m_idle[(unsigned int)DIR::FRONT]);
}

void GunnerBaseAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (IsPlayingIdle())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR::FRONT])
			{
				PlayAnimation(m_idle[(unsigned int)DIR::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR::FRONT_DIAGONAL])
			{
				PlayAnimation(m_idle[(unsigned int)DIR::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR::SIDE])
			{
				PlayAnimation(m_idle[(unsigned int)DIR::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR::BACK_DIAGONAL])
			{
				PlayAnimation(m_idle[(unsigned int)DIR::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_idle[(unsigned int)DIR::BACK])
			{
				PlayAnimation(m_idle[(unsigned int)DIR::BACK], false, true);
			}

			ResetUVDirection();
		}

	}
	else if (IsPlayingWalk())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR::FRONT])
			{
				PlayAnimation(m_walk[(unsigned int)DIR::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR::FRONT_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR::SIDE])
			{
				PlayAnimation(m_walk[(unsigned int)DIR::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR::BACK_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_walk[(unsigned int)DIR::BACK])
			{
				PlayAnimation(m_walk[(unsigned int)DIR::BACK], false, true);
			}

			ResetUVDirection();
		}
	}
}

void GunnerBaseAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for (int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_idle[i]);

	for (int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_walk[i]);

	SafeDelete(m_shoot);

	for (int i = 0; i < (int)DIE::MAX; ++i)
		SafeDelete(m_die[i]);

	for (int i = 0; i < (int)DAMAGE::MAX; ++i)
		SafeDelete(m_damage[i]);
}

void GunnerBaseAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	for (int i = 0; i < (int)DIE::MAX; ++i)
	{
		if (current == m_die[i])
		{
			SetDefaultAnimation(nullptr);
			OnDeadAnimated();
		}
	}
}

void GunnerBaseAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void GunnerBaseAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void GunnerBaseAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void GunnerBaseAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}

void GunnerBaseAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void GunnerBaseAnimator::PlayIdle()
{
	if (IsPlayingIdle())
	{
		return;
	}
	PlayAnimation(m_idle[(unsigned int)DIR::FRONT]);
}

void GunnerBaseAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}
	PlayAnimation(m_walk[(unsigned int)DIR::FRONT]);
}

void GunnerBaseAnimator::PlayShoot()
{
	PlayAnimation(m_shoot, true);
	ResetUVDirection();
}

void GunnerBaseAnimator::PlayDie(DIE type)
{
	PlayAnimation(m_die[unsigned int(type)]);
	ResetUVDirection();
}

void GunnerBaseAnimator::PlayDamage(DAMAGE type)
{
	PlayAnimation(m_damage[unsigned int(type)], true);
	ResetUVDirection();
}

bool GunnerBaseAnimator::IsPlayingIdle() const
{
	for (auto idle : m_idle)
	{
		if (currentAnimation == idle)
		{
			return true;
		}
	}
	return false;
}

bool GunnerBaseAnimator::IsPlayingWalk() const
{
	for (auto walk : m_walk)
	{
		if (currentAnimation == walk)
		{
			return true;
		}
	}
	return false;
}

bool GunnerBaseAnimator::IsPlayingShoot() const
{
	return currentAnimation == m_shoot;
}

bool GunnerBaseAnimator::IsPlayingDie() const
{
	for (auto die : m_die)
	{
		if (currentAnimation == die)
		{
			return true;
		}
	}
	return false;
}

bool GunnerBaseAnimator::IsPlayingDamage() const
{
	for (auto damage : m_damage)
	{
		if (currentAnimation == damage)
		{
			return true;
		}
	}
	return false;
}
