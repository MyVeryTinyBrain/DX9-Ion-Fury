#include "shared_stdafx.h"
#include "BowAnimator.h"
#include "SpriteAnimation.h"

void BowAnimator::Awake()
{
	m_beginIdle = new SpriteAnimation;
	m_beginIdle->AddTexture(L"../SharedResource/Texture/bow/fire0.png");

	m_idle = new SpriteAnimation;
	m_idle->AddTexture(L"../SharedResource/Texture/bow/fire0.png");
	m_idle->isLoop = true;

	m_beginShoot = new SpriteAnimation;
	m_beginShoot->AddTexture(L"../SharedResource/Texture/bow/fire0.png");
	m_beginShoot->AddTexture(L"../SharedResource/Texture/bow/fire1.png");
	m_beginShoot->AddTexture(L"../SharedResource/Texture/bow/fire2.png");
	m_beginShoot->interval = 0.02f;

	m_shootRecoil = new SpriteAnimation;
	m_shootRecoil->AddTexture(L"../SharedResource/Texture/bow/fire3.png");
	m_shootRecoil->AddTexture(L"../SharedResource/Texture/bow/fire4.png");
	m_shootRecoil->AddTexture(L"../SharedResource/Texture/bow/fire5.png");
	m_shootRecoil->AddTexture(L"../SharedResource/Texture/bow/fire6.png");
	m_shootRecoil->interval = 0.02f;

	m_pullString = new SpriteAnimation;
	m_pullString->AddTexture(L"../SharedResource/Texture/bow/fire2.png");
	m_pullString->AddTexture(L"../SharedResource/Texture/bow/fire1.png");
	m_pullString->AddTexture(L"../SharedResource/Texture/bow/fire0.png");
	m_pullString->interval = 0.1f;

	m_reload = new SpriteAnimation;
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload0.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload1.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload2.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload3.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload4.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload5.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload6.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload7.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload8.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload9.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload10.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload11.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload12.png");
	m_reload->AddTexture(L"../SharedResource/Texture/bow/reload13.png");

	SetDefaultAnimation(m_idle);
}

void BowAnimator::OnDestroy()
{
	SafeDelete(m_beginIdle);

	SafeDelete(m_idle);

	SafeDelete(m_beginShoot);

	SafeDelete(m_shootRecoil);

	SafeDelete(m_pullString);

	SafeDelete(m_reload);
}

void BowAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	if (current == m_beginIdle)
	{
		PlayAnimation(m_idle);
	}

	if (current == m_beginShoot)
	{
		PlayAnimation(m_shootRecoil);
		OnShoot();
	}

	if (current == m_shootRecoil)
	{
		PlayAnimation(m_pullString);
	}

	if (current == m_reload)
	{
		OnReloaded();
	}
}

void BowAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void BowAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void BowAnimator::PlayIdle()
{
	PlayAnimation(m_beginIdle);
}

void BowAnimator::PlayShoot()
{
	PlayAnimation(m_beginShoot);
}

void BowAnimator::PlayReload()
{
	PlayAnimation(m_reload);
}

bool BowAnimator::IsPlayingIdle() const
{
	return currentAnimation == m_beginIdle || currentAnimation == m_idle;
}

bool BowAnimator::IsPlayingShoot() const
{
	return currentAnimation == m_beginShoot || currentAnimation == m_pullString;
}

bool BowAnimator::IsPlayingReload() const
{
	return currentAnimation == m_reload;
}

bool BowAnimator::IsPlayingPullString() const
{
	return currentAnimation == m_pullString;
}
