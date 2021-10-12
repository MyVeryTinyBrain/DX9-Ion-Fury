#include "stdafx.h"
#include "RevolverAnimator.h"
#include "SpriteAnimation.h"

void RevolverAnimator::Awake()
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
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver4.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver4.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver4.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");
	m_shoot->interval = 0.01f;

	m_beginReload = new SpriteAnimation;
	m_beginReload->AddTexture(L"../SharedResource/Texture/revolver/revolver6.png");
	m_beginReload->AddTexture(L"../SharedResource/Texture/revolver/revolver10.png");
	m_beginReload->AddTexture(L"../SharedResource/Texture/revolver/revolver11.png");
	m_beginReload->AddTexture(L"../SharedResource/Texture/revolver/revolver12.png");
	m_beginReload->AddTexture(L"../SharedResource/Texture/revolver/revolver13.png");
	m_beginReload->AddTexture(L"../SharedResource/Texture/revolver/revolver14.png");
	m_beginReload->interval = 0.1f;

	m_reloadingPutin = new SpriteAnimation;
	m_reloadingPutin->AddTexture(L"../SharedResource/Texture/revolver/revolver14.png");
	m_reloadingPutin->interval = 0.4f;

	m_reloadingPullout = new SpriteAnimation;
	m_reloadingPullout->AddTexture(L"../SharedResource/Texture/revolver/revolver9.png");
	m_reloadingPullout->interval = 0.4f;

	m_endReload = new SpriteAnimation;
	m_endReload->AddTexture(L"../SharedResource/Texture/revolver/revolver9.png");
	m_endReload->AddTexture(L"../SharedResource/Texture/revolver/revolver8.png");
	m_endReload->AddTexture(L"../SharedResource/Texture/revolver/revolver7.png");
	m_endReload->AddTexture(L"../SharedResource/Texture/revolver/revolver6.png");
	m_endReload->AddTexture(L"../SharedResource/Texture/revolver/revolver5.png");

	SetDefaultAnimation(m_default);
}

void RevolverAnimator::OnDestroy()
{
	SafeDelete(m_default);

	SafeDelete(m_shoot);

	SafeDelete(m_beginReload);

	SafeDelete(m_reloadingPutin);

	SafeDelete(m_reloadingPullout);

	SafeDelete(m_endReload);
}

void RevolverAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	if (current == m_reloadingPutin)
	{
		OnReloaded();
	}
}

void RevolverAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
	if (*next == m_default)
	{
		if (current == m_beginReload)
		{
			*next = m_reloadingPutin;
		}
		else if (current == m_reloadingPutin)
		{
			*next = m_reloadingPullout;
		}
		else if (current == m_reloadingPullout)
		{
			*next = m_endReload;
		}
	}
}

void RevolverAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void RevolverAnimator::PlayShoot()
{
	PlayAnimation(m_shoot);
}

void RevolverAnimator::PlayReload()
{
	PlayAnimation(m_beginReload);
}

bool RevolverAnimator::IsPlayingIdle() const
{
	return currentAnimation == m_default;
}

bool RevolverAnimator::IsPlayingShoot() const
{
	return currentAnimation == m_shoot;
}

bool RevolverAnimator::IsPlayingReload() const
{
	if (currentAnimation == m_beginReload) return true;
	if (currentAnimation == m_reloadingPutin) return true;
	if (currentAnimation == m_reloadingPullout) return true;
	if (currentAnimation == m_endReload) return true;
	return false;
}

bool RevolverAnimator::IsPlayingReloadPutin() const
{
	return currentAnimation == m_reloadingPutin;
}
