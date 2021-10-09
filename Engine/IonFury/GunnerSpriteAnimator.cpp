#include "stdafx.h"
#include "GunnerSpriteAnimator.h"
#include "SpriteAnimation.h"

void GunnerSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle = new SpriteAnimation;
	m_idle->AddTexture(L"../SharedResource/Texture/gunner/gunner_fire0.png");
	m_idle->isLoop = true;

	m_walk[(unsigned int)DIR::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk0.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk1.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk2.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_walk3.png");
	m_walk[(unsigned int)DIR::FRONT]->interval = 0.1f;

	m_walk[(unsigned int)DIR::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_side_walk0.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_side_walk1.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_side_walk2.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/gunner/gunner_side_walk3.png");
	m_walk[(unsigned int)DIR::SIDE]->interval = 0.1f;

	m_walk[(unsigned int)DIR::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_back_walk0.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_back_walk1.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_back_walk2.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_back_walk3.png");
	m_walk[(unsigned int)DIR::BACK]->interval = 0.1f;

	SetDefaultAnimation(m_idle);
}

void GunnerSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_idle);

	for(int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_walk[i]);
}

void GunnerSpriteAnimator::OnAnimationEnd()
{
}

void GunnerSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void GunnerSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void GunnerSpriteAnimator::PlayIdle()
{
	PlayAnimation(m_idle);
}

void GunnerSpriteAnimator::PlayWalk(DIR direction)
{
	PlayAnimation(m_walk[unsigned int(direction)]);
}
