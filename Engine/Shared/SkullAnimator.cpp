#include "shared_stdafx.h"
#include "SkullAnimator.h"
#include "SpriteAnimation.h"

void SkullAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(int)DIR::FRONT] = new SpriteAnimation;
	m_idle[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/idle_front0.png");
	m_idle[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/idle_front1.png");
	m_idle[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/idle_front2.png");
	m_idle[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/idle_front3.png");
	m_idle[(int)DIR::FRONT]->isLoop = true;

	m_idle[(int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_idle[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_front_diagonal0.png");
	m_idle[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_front_diagonal1.png");
	m_idle[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_front_diagonal2.png");
	m_idle[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_front_diagonal3.png");
	m_idle[(int)DIR::FRONT_DIAGONAL]->isLoop = true;

	m_idle[(int)DIR::SIDE] = new SpriteAnimation;
	m_idle[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/idle_side0.png");
	m_idle[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/idle_side1.png");
	m_idle[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/idle_side2.png");
	m_idle[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/idle_side3.png");
	m_idle[(int)DIR::SIDE]->isLoop = true;

	m_idle[(int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_idle[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_back_diagonal0.png");
	m_idle[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_back_diagonal1.png");
	m_idle[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_back_diagonal2.png");
	m_idle[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/idle_back_diagonal3.png");
	m_idle[(int)DIR::BACK_DIAGONAL]->isLoop = true;

	m_idle[(int)DIR::BACK] = new SpriteAnimation;
	m_idle[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/idle_back0.png");
	m_idle[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/idle_back1.png");
	m_idle[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/idle_back2.png");
	m_idle[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/idle_back3.png");
	m_idle[(int)DIR::BACK]->isLoop = true;

	m_walk[(int)DIR::FRONT] = new SpriteAnimation;
	m_walk[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/walk_front0.png");
	m_walk[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/walk_front1.png");
	m_walk[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/walk_front2.png");
	m_walk[(int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/skull/walk_front3.png");
	m_walk[(int)DIR::FRONT]->isLoop = true;
	m_walk[(int)DIR::FRONT]->interval = 0.1f;

	m_walk[(int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_front_diagonal0.png");
	m_walk[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_front_diagonal1.png");
	m_walk[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_front_diagonal2.png");
	m_walk[(int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_front_diagonal3.png");
	m_walk[(int)DIR::FRONT_DIAGONAL]->isLoop = true;
	m_walk[(int)DIR::FRONT_DIAGONAL]->interval = 0.1f;

	m_walk[(int)DIR::SIDE] = new SpriteAnimation;
	m_walk[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/walk_side0.png");
	m_walk[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/walk_side1.png");
	m_walk[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/walk_side2.png");
	m_walk[(int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/skull/walk_side3.png");
	m_walk[(int)DIR::SIDE]->isLoop = true;
	m_walk[(int)DIR::SIDE]->interval = 0.1f;

	m_walk[(int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_back_diagonal0.png");
	m_walk[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_back_diagonal1.png");
	m_walk[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_back_diagonal2.png");
	m_walk[(int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/skull/walk_back_diagonal3.png");
	m_walk[(int)DIR::BACK_DIAGONAL]->isLoop = true;
	m_walk[(int)DIR::BACK_DIAGONAL]->interval = 0.1f;

	m_walk[(int)DIR::BACK] = new SpriteAnimation;
	m_walk[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/walk_back0.png");
	m_walk[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/walk_back1.png");
	m_walk[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/walk_back2.png");
	m_walk[(int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/skull/walk_back3.png");
	m_walk[(int)DIR::BACK]->isLoop = true;
	m_walk[(int)DIR::BACK]->interval = 0.1f;

	m_attack = new SpriteAnimation;
	m_attack->AddTexture(L"../SharedResource/Texture/skull/attack0.png");
	m_attack->AddTexture(L"../SharedResource/Texture/skull/attack1.png");
	m_attack->AddTexture(L"../SharedResource/Texture/skull/attack2.png");
	m_attack->AddTexture(L"../SharedResource/Texture/skull/attack3.png");

	m_beginFly = new SpriteAnimation;
	m_beginFly->AddTexture(L"../SharedResource/Texture/skull/fly0.png");
	m_beginFly->AddTexture(L"../SharedResource/Texture/skull/fly1.png");
	m_beginFly->AddTexture(L"../SharedResource/Texture/skull/fly2.png");
	m_beginFly->AddTexture(L"../SharedResource/Texture/skull/fly3.png");

	m_fly = new SpriteAnimation;
	m_fly->AddTexture(L"../SharedResource/Texture/skull/fly3.png");
	m_fly->isLoop = true;

	m_land = new SpriteAnimation;
	m_land->AddTexture(L"../SharedResource/Texture/skull/fly3.png");
	m_land->AddTexture(L"../SharedResource/Texture/skull/fly2.png");
	m_land->AddTexture(L"../SharedResource/Texture/skull/fly1.png");
	m_land->AddTexture(L"../SharedResource/Texture/skull/fly0.png");

	m_die = new SpriteAnimation;
	m_die->AddTexture(L"../SharedResource/Texture/skull/die0.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die0.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die1.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die1.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die2.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die2.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die3.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die3.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die4.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die5.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die6.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die7.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die4.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die5.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die6.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die7.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die8.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die8.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die9.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die9.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die10.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die10.png");
	m_die->AddTexture(L"../SharedResource/Texture/skull/die11.png");
	m_die->interval = 0.1f;

	SetDefaultAnimation(m_idle[(int)DIR::FRONT]);
}

void SkullAnimator::LateUpdate()
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

void SkullAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for (int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_idle[i]);

	for (int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_walk[i]);

	SafeDelete(m_attack);

	SafeDelete(m_beginFly);

	SafeDelete(m_fly);

	SafeDelete(m_land);

	SafeDelete(m_die);
}

void SkullAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	if (current == m_land)
	{
		OnPlayedLand();
	}
	if (current == m_attack)
	{
		OnPlayedAttack();
	}
	if (current == m_die)
	{
		OnPlayedDie();
		SetTransitionMode(false);
	}
}

void SkullAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
	if (current == m_beginFly)
	{
		*next = m_fly;
		OnPlayedFly();
	}
}

void SkullAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void SkullAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void SkullAnimator::PlayIdle()
{
	if (IsPlayingIdle())
	{
		return;
	}
	PlayAnimation(m_idle[(unsigned int)DIR::FRONT]);
}

void SkullAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}
	PlayAnimation(m_walk[(unsigned int)DIR::FRONT]);
}

void SkullAnimator::PlayAttack()
{
	PlayAnimation(m_attack);
}

void SkullAnimator::PlayFly()
{
	PlayAnimation(m_beginFly);
}

void SkullAnimator::PlayLand()
{
	PlayAnimation(m_land);
}

void SkullAnimator::PlayDie()
{
	PlayAnimation(m_die);
}

bool SkullAnimator::IsPlayingIdle() const
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

bool SkullAnimator::IsPlayingWalk() const
{
	for (auto idle : m_walk)
	{
		if (currentAnimation == idle)
		{
			return true;
		}
	}
	return false;
}

bool SkullAnimator::IsPlayingAttack() const
{
	return currentAnimation == m_attack;
}

bool SkullAnimator::IsPlayingFlyAnimations() const
{
	return currentAnimation == m_beginFly || currentAnimation == m_fly || currentAnimation == m_land;
}

bool SkullAnimator::IsPlayingBeginFly() const
{
	return currentAnimation == m_beginFly;
}

bool SkullAnimator::IsPlayingFly() const
{
	return currentAnimation == m_fly;
}

bool SkullAnimator::IsPlayingLand() const
{
	return currentAnimation == m_land;
}

bool SkullAnimator::IsPlayingDie() const
{
	return currentAnimation == m_die;
}

void SkullAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void SkullAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
