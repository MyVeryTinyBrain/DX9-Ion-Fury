#include "stdafx.h"
#include "SpiderSpriteAnimator.h"
#include "SpriteAnimation.h"

void SpiderSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

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

	SetDefaultAnimation(m_walk[(unsigned int)DIR_SPIDER::FRONT]);
}

void SpiderSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

}

void SpiderSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for (int i = 0; i < (int)DIR_SPIDER::MAX; ++i)
		SafeDelete(m_walk[i]);
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

void SpiderSpriteAnimator::PlayWalk()
{
	PlayAnimation(m_walk[(unsigned int)DIR_SPIDER::FRONT]);
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
