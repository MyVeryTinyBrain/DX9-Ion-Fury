#include "shared_stdafx.h"
#include "ObjectRatAnimator.h"
#include "SpriteAnimation.h"

void ObjectRatAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(unsigned int)DIR::FRONT] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::FRONT]->isLoop = true;
	m_idle[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/rat/front0.png");

	m_idle[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->isLoop = true;
	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/front_diagonal0.png");

	m_idle[(unsigned int)DIR::SIDE] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::SIDE]->isLoop = true;
	m_idle[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/rat/side0.png");

	m_idle[(unsigned int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->isLoop = true;
	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/back_diagonal0.png");

	m_idle[(unsigned int)DIR::BACK] = new SpriteAnimation;
	m_idle[(unsigned int)DIR::BACK]->isLoop = true;
	m_idle[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/rat/back0.png");

	m_walk[(unsigned int)DIR::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT]->interval = 0.1f;
	m_walk[(unsigned int)DIR::FRONT]->isLoop = true;
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/rat/front0.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/rat/front1.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/rat/front2.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/rat/front3.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/rat/front4.png");

	m_walk[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->interval = 0.1f;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->isLoop = true;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/front_diagonal0.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/front_diagonal1.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/front_diagonal2.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/front_diagonal3.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/front_diagonal4.png");

	m_walk[(unsigned int)DIR::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::SIDE]->interval = 0.1f;
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/rat/side0.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/rat/side1.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/rat/side2.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/rat/side3.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/rat/side4.png");

	m_walk[(unsigned int)DIR::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->interval = 0.1f;
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/back_diagonal0.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/back_diagonal1.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/back_diagonal2.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/back_diagonal3.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/rat/back_diagonal4.png");

	m_walk[(unsigned int)DIR::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::BACK]->interval = 0.1f;
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/rat/back0.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/rat/back1.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/rat/back2.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/rat/back3.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/rat/back4.png");

	SetDefaultAnimation(m_idle[(unsigned int)DIR::FRONT]);
}

void ObjectRatAnimator::LateUpdate()
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

void ObjectRatAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for (int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_idle[i]);

	for (int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_walk[i]);
}

void ObjectRatAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
}

void ObjectRatAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void ObjectRatAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void ObjectRatAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void ObjectRatAnimator::PlayIdle()
{
	if (IsPlayingIdle())
	{
		return;
	}
	PlayAnimation(m_idle[(unsigned int)DIR::FRONT]);
}

void ObjectRatAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}
	PlayAnimation(m_walk[(unsigned int)DIR::FRONT]);
}

bool ObjectRatAnimator::IsPlayingIdle() const
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

bool ObjectRatAnimator::IsPlayingWalk() const
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

void ObjectRatAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? +1.0f : -1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void ObjectRatAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
