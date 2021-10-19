#include "shared_stdafx.h"
#include "ChaingunGunpartAnimator.h"
#include "SpriteAnimation.h"

void ChaingunGunpartAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_default = new SpriteAnimation;
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/gun0.png");
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/gun1.png");
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/gun2.png");
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/gun3.png");
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/gun4.png");
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/gun5.png");
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/gun6.png");
	m_default->interval = 0.1f;
	m_default->isLoop = true;

	SetDefaultAnimation(m_default);
}

void ChaingunGunpartAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_default);
}

void ChaingunGunpartAnimator::AnimationUpdate()
{
	SpriteAnimator::AnimationUpdate();

	unsigned int frame = currentAnimation->TimeToIndex(GetElapsedTime());

	if (currentAnimation->textureCount > 0)
	{
		frame %= m_default->textureCount;
	}

	if (frame < m_beforeFrame)
	{
		OnRotatedBarrel();
	}

	m_beforeFrame = frame;
}

void ChaingunGunpartAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
}

void ChaingunGunpartAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void ChaingunGunpartAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}
