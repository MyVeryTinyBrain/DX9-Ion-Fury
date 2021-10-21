#include "shared_stdafx.h"
#include "SkullBallAnimator.h"
#include "SpriteAnimation.h"

void SkullBallAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_animation = new SpriteAnimation;
	m_animation->AddTexture(L"../SharedResource/Texture/skull/ball0.png");
	m_animation->AddTexture(L"../SharedResource/Texture/skull/ball1.png");
	m_animation->AddTexture(L"../SharedResource/Texture/skull/ball2.png");
	m_animation->AddTexture(L"../SharedResource/Texture/skull/ball3.png");
	m_animation->isLoop = true;

	SetDefaultAnimation(m_animation);
}

void SkullBallAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_animation);
}

void SkullBallAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
}

void SkullBallAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void SkullBallAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}
