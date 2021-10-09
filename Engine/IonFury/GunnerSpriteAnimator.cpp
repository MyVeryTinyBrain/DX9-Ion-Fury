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

	m_shoot = new SpriteAnimation;
	m_shoot->AddTexture(L"../SharedResource/Texture/gunner/gunner_fire0.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/gunner/gunner_fire1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/gunner/gunner_fire2.png");

	m_die[(unsigned int)DIE::DIE_HEADSHOT] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot0.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot1.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot2.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot3.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot4.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_bodyshot5.png");

	m_die[(unsigned int)DIE::DIE_BODYSHOT] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot0.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot1.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot2.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot3.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot4.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot5.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/gunner/gunner_headshot6.png");

	m_die[(unsigned int)DIE::DIE_EXPLOSION] = new SpriteAnimation;
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion0.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion1.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion2.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion3.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion4.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion5.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion6.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion7.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion8.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK] = new SpriteAnimation;
	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK]->AddTexture(L"../SharedResource/Texture/gunner/gunner_damaged.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC] = new SpriteAnimation;
	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC]->AddTexture(L"../SharedResource/Texture/gunner/gunner_explosion8.png");

	SetDefaultAnimation(m_idle);
}

void GunnerSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_idle);

	for(int i = 0; i < (int)DIR::MAX; ++i)
		SafeDelete(m_walk[i]);

	SafeDelete(m_shoot);

	for (int i = 0; i < (int)DIE::MAX; ++i)
		SafeDelete(m_die[i]);

	for (int i = 0; i < (int)DAMAGE::MAX; ++i)
		SafeDelete(m_damage[i]);
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
