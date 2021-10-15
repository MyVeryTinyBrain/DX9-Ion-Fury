#include "stdafx.h"
#include "ChaingunAmmopartAnimator.h"
#include "SpriteAnimation.h"

void ChaingunAmmopartAnimator::Awake()
{
	m_default = new SpriteAnimation;
	m_default->AddTexture(L"../SharedResource/Texture/chaingun/ammo0.png");
	m_default->isLoop = true;

	m_anim = new SpriteAnimation;
	m_anim->AddTexture(L"../SharedResource/Texture/chaingun/ammo1.png");
	m_anim->AddTexture(L"../SharedResource/Texture/chaingun/ammo2.png");
	m_anim->AddTexture(L"../SharedResource/Texture/chaingun/ammo3.png");
	m_anim->AddTexture(L"../SharedResource/Texture/chaingun/ammo4.png");
	m_anim->AddTexture(L"../SharedResource/Texture/chaingun/ammo5.png");
	m_anim->AddTexture(L"../SharedResource/Texture/chaingun/ammo6.png");
	m_anim->interval = 0.02f;

	SetDefaultAnimation(m_default);
}

void ChaingunAmmopartAnimator::OnDestroy()
{
	SafeDelete(m_default);

	SafeDelete(m_anim);
}

void ChaingunAmmopartAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
}

void ChaingunAmmopartAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void ChaingunAmmopartAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void ChaingunAmmopartAnimator::PlayIdle()
{
	PlayAnimation(m_default);
}

void ChaingunAmmopartAnimator::PlayAnim()
{
	PlayAnimation(m_anim);
}
