#include "stdafx.h"
#include "WarmechSpriteAnimator.h"
#include "SpriteAnimation.h"

void WarmechSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(unsigned int)DIR_WARMECH::FRONT] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_front.png");
	m_idle[(unsigned int)DIR_WARMECH::FRONT]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_front_diagonal.png");
	m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::SIDE] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_side.png");
	m_idle[(unsigned int)DIR_WARMECH::SIDE]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_back_diagonal.png");
	m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::BACK] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_back.png");
	m_idle[(unsigned int)DIR_WARMECH::BACK]->isLoop = true;

	m_walk[(unsigned int)DIR_WARMECH::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front0.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front1.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front2.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front3.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->interval = 0.1f;
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->isLoop = true;
	
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal0.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal1.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal2.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal3.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->interval = 0.1f;
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->isLoop = true;
	  
	m_walk[(unsigned int)DIR_WARMECH::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side0.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side1.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side2.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side3.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->interval = 0.1f;
	 
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal3.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->interval = 0.1f;
	
	m_walk[(unsigned int)DIR_WARMECH::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back0.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back1.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back2.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back3.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->interval = 0.1f;

	m_shoot = new SpriteAnimation;
	m_shoot->AddTexture(L"../SharedResource/Texture/warmech/warmech_shot0.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/warmech/warmech_shot1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/warmech/warmech_shot2.png");
	m_shoot->interval = 0.05f;

	m_missile = new SpriteAnimation;
	m_missile->AddTexture(L"../SharedResource/Texture/warmech/warmech_missile0.png");
	m_missile->AddTexture(L"../SharedResource/Texture/warmech/warmech_missile1.png");
	m_missile->AddTexture(L"../SharedResource/Texture/warmech/warmech_missile2.png");
	m_missile->interval = 0.1f;

	SetDefaultAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT]);
}

void WarmechSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (IsPlayingIdle())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_WARMECH::FRONT])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_WARMECH::SIDE])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_WARMECH::BACK])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::BACK], false, true);
			}

			ResetUVDirection();
		}

	}
	else if (IsPlayingWalk())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::FRONT])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::SIDE])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::BACK])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::BACK], false, true);
			}

			ResetUVDirection();
		}
	}
}

void WarmechSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for(int i = 0; i < (int)DIR_WARMECH::MAX; ++i)
		SafeDelete(m_idle[i]);

	for (int i = 0; i < (int)DIR_WARMECH::MAX; ++i)
		SafeDelete(m_walk[i]);

	SafeDelete(m_shoot);

	SafeDelete(m_missile);
}

void WarmechSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{

}

void WarmechSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WarmechSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WarmechSpriteAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void WarmechSpriteAnimator::PlayIdle()
{
	if (IsPlayingIdle())
	{
		return;
	}
	PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT]);
}

void WarmechSpriteAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}
	PlayAnimation(m_walk [(unsigned int)DIR_WARMECH::FRONT] );
}

void WarmechSpriteAnimator::PlayShoot()
{
	PlayAnimation(m_shoot, true);
}

void WarmechSpriteAnimator::PlayMissile()
{
	PlayAnimation(m_missile, true);
}

bool WarmechSpriteAnimator::IsPlayingIdle() const
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

bool WarmechSpriteAnimator::IsPlayingWalk() const
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

bool WarmechSpriteAnimator::IsPlayingShoot() const
{
	return currentAnimation == m_shoot;
}

bool WarmechSpriteAnimator::IsPlayingMissile() const
{
	return currentAnimation == m_missile;
}

SpriteAnimation* WarmechSpriteAnimator::GetIdle() const
{
	return m_idle[(unsigned int)DIR_WARMECH::FRONT];
}

SpriteAnimation* WarmechSpriteAnimator::GetWalk() const
{
	return m_walk[(unsigned int)DIR_WARMECH::FRONT];
}

SpriteAnimation* WarmechSpriteAnimator::GetShoot() const
{
	return m_shoot;
}

SpriteAnimation* WarmechSpriteAnimator::GetMissile() const
{
	return m_missile;
}

void WarmechSpriteAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void WarmechSpriteAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
