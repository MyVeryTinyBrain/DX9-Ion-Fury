#include "stdafx.h"
#include "RightHandAnimator.h"
#include "SpriteAnimation.h"

void RightHandAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_default = new SpriteAnimation;
	m_default->AddTexture(L"../SharedResource/Texture/revolver/revolver0.png");
	m_default->isLoop = true;

	m_shoot = new SpriteAnimation;
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver2.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver3.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver3.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver3.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver3.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver4.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver4.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver4.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver4.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->interval = 0.01f;

	SetDefaultAnimation(m_default);
}

void RightHandAnimator::OnDestroy()
{
	SafeDelete(m_default);
	SafeDelete(m_shoot);
}

void RightHandAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
}

void RightHandAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void RightHandAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void RightHandAnimator::PlayShoot()
{
	PlayAnimation(m_shoot);
}
