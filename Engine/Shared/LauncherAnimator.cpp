#include "shared_stdafx.h"
#include "LauncherAnimator.h"
#include "SpriteAnimation.h"
#include "SoundMgr.h"

void LauncherAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(int)Skin::Red] = new SpriteAnimation;
	m_idle[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red0.png");

	m_idle[(int)Skin::Yellow] = new SpriteAnimation;
	m_idle[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow0.png");

	m_beginIdle[(int)Skin::Red] = new SpriteAnimation;
	m_beginIdle[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red0.png");

	m_beginIdle[(int)Skin::Yellow] = new SpriteAnimation;
	m_beginIdle[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow0.png");

	m_shoot[(int)Skin::Red] = new SpriteAnimation;
	m_shoot[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red0.png");
	m_shoot[(int)Skin::Red]->interval = 0.2f;

	m_shoot[(int)Skin::Yellow] = new SpriteAnimation;
	m_shoot[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow0.png");
	m_shoot[(int)Skin::Yellow]->interval = 0.2f;

	m_pullPump[(int)Skin::Red] = new SpriteAnimation;
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red0.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red1.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red2.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red3.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red4.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red5.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red6.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red7.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red8.png");
	m_pullPump[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red0.png");

	m_pullPump[(int)Skin::Yellow] = new SpriteAnimation;
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow0.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow1.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow2.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow3.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow4.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow5.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow6.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow7.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow8.png");
	m_pullPump[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow0.png");

	m_beginReload[(int)Skin::Red] = new SpriteAnimation;
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red10.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red11.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red12.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red13.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red14.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red16.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red17.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red18.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red19.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red23.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red24.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red24.png");
	m_beginReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red23.png");

	m_endReload[(int)Skin::Red] = new SpriteAnimation;
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red19.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red18.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red17.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red16.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red14.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red13.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red12.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red11.png");
	m_endReload[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red10.png");

	m_beginReload[(int)Skin::Yellow] = new SpriteAnimation;
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow10.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow11.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow12.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow13.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow14.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow16.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow17.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow18.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow19.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow23.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow24.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow24.png");
	m_beginReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow23.png");

	m_endReload[(int)Skin::Yellow] = new SpriteAnimation;
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow19.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow18.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow17.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow16.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow14.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow13.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow12.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow11.png");
	m_endReload[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow10.png");

	m_beginSkinChange[(int)Skin::Red] = new SpriteAnimation;
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow10.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow11.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow12.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow13.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow14.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow16.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow17.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow18.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow19.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow23.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow24.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red24.png");
	m_beginSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red23.png");

	m_endSkinChange[(int)Skin::Red] = new SpriteAnimation;
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red19.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red18.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red17.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red16.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red14.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red13.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red12.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red11.png");
	m_endSkinChange[(int)Skin::Red]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red10.png");

	m_beginSkinChange[(int)Skin::Yellow] = new SpriteAnimation;
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red10.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red11.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red12.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red13.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red14.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red16.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red17.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red18.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red19.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red23.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red24.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_red/launcher_red25.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow25.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow24.png");
	m_beginSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow23.png");

	m_endSkinChange[(int)Skin::Yellow] = new SpriteAnimation;
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow19.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow18.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow17.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow16.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow14.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow13.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow12.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow11.png");
	m_endSkinChange[(int)Skin::Yellow]->AddTexture(L"../SharedResource/Texture/launcher_yellow/launcher_yellow10.png");

	SetDefaultAnimation(m_idle[(int)m_skin]);
}

void LauncherAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_idle[(int)Skin::Red]);

	SafeDelete(m_idle[(int)Skin::Yellow]);

	SafeDelete(m_beginIdle[(int)Skin::Red]);

	SafeDelete(m_beginIdle[(int)Skin::Yellow]);

	SafeDelete(m_shoot[(int)Skin::Red]);

	SafeDelete(m_shoot[(int)Skin::Yellow]);

	SafeDelete(m_pullPump[(int)Skin::Red]);

	SafeDelete(m_pullPump[(int)Skin::Yellow]);

	SafeDelete(m_beginReload[(int)Skin::Red]);

	SafeDelete(m_beginReload[(int)Skin::Yellow]);

	SafeDelete(m_endReload[(int)Skin::Red]);

	SafeDelete(m_endReload[(int)Skin::Yellow]);

	SafeDelete(m_beginSkinChange[(int)Skin::Red]);

	SafeDelete(m_beginSkinChange[(int)Skin::Yellow]);

	SafeDelete(m_endSkinChange[(int)Skin::Red]);

	SafeDelete(m_endSkinChange[(int)Skin::Yellow]);
}

void LauncherAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (current == m_endReload[i])
		{
			OnReloaded();
		}
	}

	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (current == m_endSkinChange[i])
		{
			OnSkinChanged();
		}
	}
}

void LauncherAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (current == m_beginIdle[i])
		{
			*next = m_idle[i];
			break;
		}
	}

	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (current == m_shoot[i] && *next == m_idle[i])
		{
			*next = m_pullPump[i];
			SoundMgr::Play(L"../SharedResource/Sound/launcher/reload_0.ogg", CHANNELID::PLAYER_WEAPON_RELOAD);
			break;
		}
	}

	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (current == m_beginReload[i])
		{
			*next = m_endReload[i];
			SoundMgr::Play(L"../SharedResource/Sound/launcher/eject_000.ogg", CHANNELID::PLAYER_WEAPON_RELOAD);
			break;
		}
	}

	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (current == m_beginSkinChange[i])
		{
			*next = m_endSkinChange[i];
			SoundMgr::Play(L"../SharedResource/Sound/launcher/eject_000.ogg", CHANNELID::PLAYER_WEAPON_RELOAD);
			break;
		}
	}
}

void LauncherAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void LauncherAnimator::SetSkin(Skin value)
{
	m_skin = value;
	SetDefaultAnimation(m_idle[(int)m_skin], true);
}

void LauncherAnimator::PlayIdle()
{
	PlayAnimation(m_beginIdle[(int)m_skin]);
}

void LauncherAnimator::PlayShoot()
{
	PlayAnimation(m_shoot[(int)m_skin]);

	switch (m_skin)
	{
		case Skin::Red:
			{
				int soundIndex = rand() % 2;
				wchar_t buffer[256];
				swprintf_s(buffer, L"../SharedResource/Sound/launcher/fire_%d.ogg", soundIndex);
				SoundMgr::Play(buffer, CHANNELID::PLAYER_WEAPON_FIRE0);
			}
			break;
		case Skin::Yellow:
			{
				SoundMgr::Play(L"../SharedResource/Sound/launcher/glaunch.ogg", CHANNELID::PLAYER_WEAPON_FIRE0);
			}
			break;
	}
}

void LauncherAnimator::PlayReload()
{
	PlayAnimation(m_beginReload[(int)m_skin]);

	SoundMgr::Play(L"../SharedResource/Sound/launcher/apart_000.ogg", CHANNELID::PLAYER_WEAPON_RELOAD);
}

void LauncherAnimator::PlayChangeToRed()
{
	SetSkin(Skin::Red);
	PlayAnimation(m_beginSkinChange[(int)m_skin]);

	SoundMgr::Play(L"../SharedResource/Sound/launcher/apart_000.ogg", CHANNELID::PLAYER_WEAPON_RELOAD);
}

void LauncherAnimator::PlayChangeToYellow()
{
	SetSkin(Skin::Yellow);
	PlayAnimation(m_beginSkinChange[(int)m_skin]);

	SoundMgr::Play(L"../SharedResource/Sound/launcher/apart_000.ogg", CHANNELID::PLAYER_WEAPON_RELOAD);
}

bool LauncherAnimator::IsPlayingIdle() const
{
	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (currentAnimation == m_idle[i] || currentAnimation == m_beginIdle[i])
		{
			return true;
		}
	}

	return false;
}

bool LauncherAnimator::IsPlayingShoot() const
{
	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (currentAnimation == m_shoot[i])
		{
			return true;
		}
	}

	return false;
}

bool LauncherAnimator::IsPlayingPullPump() const
{
	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (currentAnimation == m_pullPump[i])
		{
			return true;
		}
	}

	return false;
}

bool LauncherAnimator::IsPlayingReload() const
{
	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (currentAnimation == m_beginReload[i])
		{
			return true;
		}
	}

	return false;
}

bool LauncherAnimator::IsPlayingSkinChange() const
{
	for (int i = 0; i < (int)Skin::Max; ++i)
	{
		if (currentAnimation == m_beginSkinChange[i])
		{
			return true;
		}
	}

	return false;
}
