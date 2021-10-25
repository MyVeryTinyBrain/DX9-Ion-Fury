#include "shared_stdafx.h"
#include "WebSpriteAnimator.h"
#include "SpriteAnimation.h"


void WebSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_web = new SpriteAnimation;
	m_web->AddTexture(L"../SharedResource/Texture/spider/Web0.png");
	m_web->AddTexture(L"../SharedResource/Texture/spider/Web1.png");
	m_web->AddTexture(L"../SharedResource/Texture/spider/Web2.png");
	m_web->interval = 0.15f;
}

void WebSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_web);

}

void WebSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	if (currentAnimation == m_web)
		SetTransitionMode(false);
}

void WebSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WebSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WebSpriteAnimator::PlayWeb()
{
	PlayAnimation(m_web, true);
}

bool WebSpriteAnimator::IsPlayingWeb() const
{
	return  currentAnimation == m_web;
}

SpriteAnimation* WebSpriteAnimator::GetWeb() const
{
	return m_web;
}
