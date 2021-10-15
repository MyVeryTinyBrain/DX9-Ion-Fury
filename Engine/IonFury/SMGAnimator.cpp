#include "stdafx.h"
#include "SMGAnimator.h"
#include "SpriteAnimation.h"

void SMGAnimator::Awake()
{
	m_beginIdle = new SpriteAnimation;
	m_beginIdle->AddTexture(L"../SharedResource/Texture/smg/fire0.png");

	m_idle = new SpriteAnimation;
	m_idle->AddTexture(L"../SharedResource/Texture/smg/fire0.png");

	m_fire = new SpriteAnimation;
	m_fire->AddTexture(L"../SharedResource/Texture/smg/fire0.png");
	m_fire->AddTexture(L"../SharedResource/Texture/smg/fire1.png");
	m_fire->AddTexture(L"../SharedResource/Texture/smg/fire2.png");
	m_fire->interval = 0.03f;

	m_reload = new SpriteAnimation;
	m_reload->AddTexture(L"../SharedResource/Texture/smg/angle0.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/angle1.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/angle2.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload0.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload1.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload2.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload3.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload4.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload5.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload6.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload7.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload8.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload9.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload10.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/reload11.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/angle0.png");
	m_reload->AddTexture(L"../SharedResource/Texture/smg/fire0.png");

	m_putin = new SpriteAnimation;
	m_putin->AddTexture(L"../SharedResource/Texture/smg/fire0.png");
	m_putin->interval = 0.2f;

	m_pullout = new SpriteAnimation;
	m_pullout->AddTexture(L"../SharedResource/Texture/smg/fire0.png");
	m_pullout->interval = 0.2f;

	SetDefaultAnimation(m_idle);
}

void SMGAnimator::OnDestroy()
{
	SafeDelete(m_beginIdle);

	SafeDelete(m_idle);

	SafeDelete(m_fire);

	SafeDelete(m_reload);

	SafeDelete(m_putin);

	SafeDelete(m_pullout);
}

void SMGAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	if (current == m_reload)
	{
		OnReloaded();
	}

	if (current == m_putin)
	{
		OnPlayedPutin();
	}
}

void SMGAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
	if (current == m_beginIdle)
	{
		*next = m_idle;
	}

	if (current != m_pullout && *next == m_pullout)
	{
		OnPlayPullout();
	}
}

void SMGAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void SMGAnimator::PlayIdle()
{
	PlayAnimation(m_beginIdle);
}

void SMGAnimator::PlayFire()
{
	PlayAnimation(m_fire);
}

void SMGAnimator::PlayReload()
{
	PlayAnimation(m_reload);
}

void SMGAnimator::PlayPutin()
{
	PlayAnimation(m_putin);
}

void SMGAnimator::PlayPullout()
{
	PlayAnimation(m_pullout);
}

bool SMGAnimator::IsPlayingIdle() const
{
	return currentAnimation == m_beginIdle || currentAnimation == m_idle;
}

bool SMGAnimator::IsPlayingFire() const
{
	return currentAnimation == m_fire;
}

bool SMGAnimator::IsPlayingReload() const
{
	return currentAnimation == m_reload;
}

bool SMGAnimator::IsPlayingPutin() const
{
	return currentAnimation == m_putin;
}

bool SMGAnimator::IsPlayingPullout() const
{
	return currentAnimation == m_pullout;
}
