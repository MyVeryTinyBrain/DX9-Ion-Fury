#include "stdafx.h"
#include "SpiderSpriteAnimator.h"
#include "SpriteAnimation.h"

void SpiderSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_Idle = new SpriteAnimation;
	m_Idle->AddTexture(L"../SharedResource/Texture/spider/Spider_idle_front.png");

	m_walk[(unsigned int)DIR_SPIDER::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front0.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front1.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front2.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front3.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front4.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front5.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->interval = 0.1f;
	m_walk[(unsigned int)DIR_SPIDER::FRONT]->isLoop = true;

	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front_diagonal0.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front_diagonal1.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front_diagonal2.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front_diagonal3.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front_diagonal4.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_front_diagonal5.png");
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->interval = 0.1f;
	m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->isLoop = true;

	m_walk[(unsigned int)DIR_SPIDER::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_Side0.png");
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_Side1.png");
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_Side2.png");
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_Side3.png");
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_Side4.png");
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_Side5.png");
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->interval = 0.1f;
	m_walk[(unsigned int)DIR_SPIDER::SIDE]->isLoop = true;

	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back_diagonal3.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back_diagonal4.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back_diagonal5.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->interval = 0.1f;
	m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->isLoop = true;

	m_walk[(unsigned int)DIR_SPIDER::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back0.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back1.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back2.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back3.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back4.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_walk_back5.png");
	m_walk[(unsigned int)DIR_SPIDER::BACK]->interval = 0.1f;
	m_walk[(unsigned int)DIR_SPIDER::BACK]->isLoop = true;

	m_jump[(unsigned int)DIR_SPIDER::FRONT] = new SpriteAnimation;
	m_jump[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_front0.png");
	m_jump[(unsigned int)DIR_SPIDER::FRONT]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_front1.png");
	m_jump[(unsigned int)DIR_SPIDER::FRONT]->interval = 0.3f;
	m_jump[(unsigned int)DIR_SPIDER::FRONT]->isLoop = true;

	m_jump[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL] = new SpriteAnimation;
	m_jump[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_front_diagonal0.png");
	m_jump[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_front_diagonal1.png");
	m_jump[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->interval = 0.3f;
	m_jump[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL]->isLoop = true;

	m_jump[(unsigned int)DIR_SPIDER::SIDE] = new SpriteAnimation;
	m_jump[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_side0.png");
	m_jump[(unsigned int)DIR_SPIDER::SIDE]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_side1.png");
	m_jump[(unsigned int)DIR_SPIDER::SIDE]->interval = 0.3f;
	m_jump[(unsigned int)DIR_SPIDER::SIDE]->isLoop = true;

	m_jump[(unsigned int)DIR_SPIDER::BACK_DIAGONAL] = new SpriteAnimation;
	m_jump[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_back_diagonal0.png");
	m_jump[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_back_diagonal1.png");
	m_jump[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->interval = 0.3f;
	m_jump[(unsigned int)DIR_SPIDER::BACK_DIAGONAL]->isLoop = true;

	m_jump[(unsigned int)DIR_SPIDER::BACK] = new SpriteAnimation;
	m_jump[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_back0.png");
	m_jump[(unsigned int)DIR_SPIDER::BACK]->AddTexture(L"../SharedResource/Texture/spider/Spider_jump_back1.png");
	m_jump[(unsigned int)DIR_SPIDER::BACK]->interval = 0.3f;
	m_jump[(unsigned int)DIR_SPIDER::BACK]->isLoop = true;

	m_damage = new SpriteAnimation;
	m_damage->AddTexture(L"../SharedResource/Texture/spider/Spider_zizizik.png");

	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT] = new SpriteAnimation;
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot0.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot1.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot2.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot3.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot4.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot5.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot6.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/spider/Spider_headshot7.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->interval = 0.1f;
	m_die[(unsigned int)DIE_SPIDER::DIE_HEADSHOT]->isLoop = true;

	m_die[(unsigned int)DIE_SPIDER::DIE_GENERIC] = new SpriteAnimation;
	m_die[(unsigned int)DIE_SPIDER::DIE_GENERIC]->AddTexture(L"../SharedResource/Texture/spider/Spider_hit0.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_GENERIC]->AddTexture(L"../SharedResource/Texture/spider/Spider_hit1.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_GENERIC]->AddTexture(L"../SharedResource/Texture/spider/Spider_hit2.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_GENERIC]->AddTexture(L"../SharedResource/Texture/spider/Spider_hit3.png");
	m_die[(unsigned int)DIE_SPIDER::DIE_GENERIC]->interval = 0.1f;
	m_die[(unsigned int)DIE_SPIDER::DIE_GENERIC]->isLoop = true;


	SetDefaultAnimation(m_walk[(unsigned int)DIR_SPIDER::FRONT]);
}

void SpiderSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (IsPlayingWalk())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_SPIDER::FRONT])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_SPIDER::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_SPIDER::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_SPIDER::SIDE])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_SPIDER::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_SPIDER::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_SPIDER::BACK])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_SPIDER::BACK], false, true);
			}

			ResetUVDirection();
		}
	}
	
}

void SpiderSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_Idle);

	for (int i = 0; i < (int)DIR_SPIDER::MAX; ++i)
		SafeDelete(m_walk[i]);

	for (int i = 0; i < (int)DIR_SPIDER::MAX; ++i)
		SafeDelete(m_jump[i]);

	SafeDelete(m_damage);

	for (int i = 0; i < (int)DIE_SPIDER::MAX; ++i)
		SafeDelete(m_die[i]);
}

void SpiderSpriteAnimator::OnAnimationEnd()
{
}

void SpiderSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void SpiderSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void SpiderSpriteAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void SpiderSpriteAnimator::PlayIdle()
{
	PlayAnimation(m_Idle, true);
}

void SpiderSpriteAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}

	PlayAnimation(m_walk[(unsigned int)DIR_SPIDER::FRONT]);
}

void SpiderSpriteAnimator::PlayJump()
{

	PlayAnimation(m_jump[(unsigned int)DIR_SPIDER::FRONT]);
}

void SpiderSpriteAnimator::PlayDamage()
{
	PlayAnimation(m_damage, true);
}

void SpiderSpriteAnimator::PlayDie(DIE_SPIDER type)
{
	PlayAnimation(m_die[(unsigned int)type]);
}

bool SpiderSpriteAnimator::IsPlayingIdle() const
{
	return currentAnimation == m_Idle;
}

bool SpiderSpriteAnimator::IsPlayingWalk() const
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

bool SpiderSpriteAnimator::IsPlayingJump() const
{
	for (auto jump : m_jump)
	{
		if (currentAnimation == jump)
		{
			return true;
		}
	}
	return false;
}

bool SpiderSpriteAnimator::IsPlayingDamage() const
{

	return currentAnimation == m_damage;
}

bool SpiderSpriteAnimator::IsPlayingDie() const
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

void SpiderSpriteAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void SpiderSpriteAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
