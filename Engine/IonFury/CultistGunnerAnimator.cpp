#include "stdafx.h"
#include "CultistGunnerAnimator.h"
#include <SpriteAnimation.h>

void CultistGunnerAnimator::InitAnimations()
{
	m_idle[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/idle_front.png");

	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/idle_front_diagonal.png");

	m_idle[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_gunner/idle_side.png");

	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/idle_back_diagonal.png");

	m_idle[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_gunner/idle_back.png");

	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front0.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front1.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front2.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front3.png");

	m_walk[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front_diagonal0.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front_diagonal1.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front_diagonal2.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_front_diagonal3.png");

	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_side0.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_side1.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_side2.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_side3.png");

	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back_diagonal3.png");

	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back0.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back1.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back2.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_gunner/walk_back3.png");

	m_shoot->AddTexture(L"../SharedResource/Texture/cultist_gunner/fire0.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/cultist_gunner/fire1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/cultist_gunner/fire2.png");

	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/bodyshot0.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/bodyshot1.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/bodyshot2.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/bodyshot3.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/bodyshot4.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/bodyshot5.png");

	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/headshot0.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/headshot1.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/headshot2.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/headshot3.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/headshot4.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_gunner/headshot5.png");

	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion0.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion1.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion2.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion3.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion4.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion5.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion6.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion7.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_gunner/explosion8.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK]->AddTexture(L"../SharedResource/Texture/cultist_gunner/zizizik.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC]->AddTexture(L"../SharedResource/Texture/cultist_gunner/damaged.png");
}
