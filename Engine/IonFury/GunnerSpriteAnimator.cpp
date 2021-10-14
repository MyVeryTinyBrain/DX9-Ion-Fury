#include "stdafx.h"
#include "GunnerSpriteAnimator.h"
#include "SpriteAnimation.h"

void GunnerSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(unsigned int)DIR::FRONT] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_idle_front.png");
	m_idle[(unsigned int)DIR::FRONT]->isLoop = true;

	m_idle[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_idle_front_diagonal.png");
	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR::SIDE] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_idle_side.png");
	m_idle[(unsigned int)DIR::SIDE]->isLoop = true;

	m_idle[(unsigned int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_idle_back_diagonal.png");
	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR::BACK] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_idle_back.png");
	m_idle[(unsigned int)DIR::BACK]->isLoop = true;

	m_walk[(unsigned int)DIR::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front0.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front1.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front2.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front3.png");
	m_walk[(unsigned int)DIR::FRONT]->interval = 0.1f;
	m_walk[(unsigned int)DIR::FRONT]->isLoop = true;

	m_walk[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front_diagonal0.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front_diagonal1.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front_diagonal2.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_front_diagonal3.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->interval = 0.1f;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->isLoop = true;

	m_walk[(unsigned int)DIR::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_side0.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_side1.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_side2.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_side3.png");
	m_walk[(unsigned int)DIR::SIDE]->interval = 0.1f;

	m_walk[(unsigned int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back_diagonal3.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->interval = 0.1f;

	m_walk[(unsigned int)DIR::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back0.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back1.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back2.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk_back3.png");
	m_walk[(unsigned int)DIR::BACK]->interval = 0.1f;

	m_shoot = new SpriteAnimation;
	m_shoot->AddTexture(L"../SharedResource/Texture/gunner/gunner_fire0.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/gunner/gunner_fire1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/gunner/gunner_fire2.png");
	m_shoot->interval = 0.05f;

	m_die[(unsigned int)DIE::DIE_HEADSHOT] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot0.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot1.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot2.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot3.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot4.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot5.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->interval = 0.1f;

	m_die[(unsigned int)DIE::DIE_BODYSHOT] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot0.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot1.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot2.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot3.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot4.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot5.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot6.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->interval = 0.1f;

	m_die[(unsigned int)DIE::DIE_EXPLOSION] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion0.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion1.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion2.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion3.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion4.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion5.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion6.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion7.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion8.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->interval = 0.1f;

	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK] = new SpriteAnimation;
	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_zizizik.png");
	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK]->interval = 0.3f;

	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC] = new SpriteAnimation;
	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC]->AddTexture(L"../SharedResource/Texture/gunner/gunner_damaged.png");
	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC]->interval = 0.3f;

	SetDefaultAnimation(m_idle[(unsigned int)DIR::FRONT]);
}

void GunnerSpriteAnimator::LateUpdate()
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

void GunnerSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for (int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_idle[i]);

	for(int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_walk[i]);

	SafeDelete(m_shoot);

	for (int i = 0; i < (int)DIE::MAX; ++i)
		SafeDelete(m_die[i]);

	for (int i = 0; i < (int)DAMAGE::MAX; ++i)
		SafeDelete(m_damage[i]);
}

void GunnerSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
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

void GunnerSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void GunnerSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void GunnerSpriteAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void GunnerSpriteAnimator::PlayIdle()
{
	if (IsPlayingIdle())
	{
		return;
	}
	PlayAnimation(m_idle[(unsigned int)DIR::FRONT]);
}

void GunnerSpriteAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}
	PlayAnimation(m_walk[(unsigned int)DIR::FRONT]);
}

void GunnerSpriteAnimator::PlayShoot()
{
	PlayAnimation(m_shoot, true);
	ResetUVDirection();
}

void GunnerSpriteAnimator::PlayDie(DIE type)
{
	PlayAnimation(m_die[unsigned int(type)]);
	ResetUVDirection();
}

void GunnerSpriteAnimator::PlayDamage(DAMAGE type)
{
	PlayAnimation(m_damage[unsigned int(type)], true);
	ResetUVDirection();
}

bool GunnerSpriteAnimator::IsPlayingIdle() const
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

bool GunnerSpriteAnimator::IsPlayingWalk() const
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

bool GunnerSpriteAnimator::IsPlayingShoot() const
{
	return currentAnimation == m_shoot;
}

bool GunnerSpriteAnimator::IsPlayingDie() const
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

bool GunnerSpriteAnimator::IsPlayingDamage() const
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

void GunnerSpriteAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void GunnerSpriteAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
