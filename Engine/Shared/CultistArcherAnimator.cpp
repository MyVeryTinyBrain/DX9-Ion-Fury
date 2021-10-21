#include "shared_stdafx.h"
#include "CultistArcherAnimator.h"
#include "SpriteAnimation.h"

void CultistArcherAnimator::InitAnimations()
{
	m_idle[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_archer/idle_front.png");

	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/idle_front_diagonal.png");

	m_idle[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_archer/idle_side.png");

	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/idle_back_diagonal.png");

	m_idle[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_archer/idle_back.png");

	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front0.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front1.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front2.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front3.png");

	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front_diagonal0.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front_diagonal1.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front_diagonal2.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_front_diagonal3.png");

	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_side0.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_side1.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_side2.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_side3.png");

	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back_diagonal3.png");

	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back0.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back1.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back2.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/cultist_archer/walk_back3.png");

	m_shoot->AddTexture(L"../SharedResource/Texture/cultist_archer/fire0.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/cultist_archer/fire1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/cultist_archer/fire2.png");

	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/bodyshot0.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/bodyshot1.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/bodyshot2.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/bodyshot3.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/bodyshot4.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/bodyshot5.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/bodyshot6.png");

	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot0.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot1.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot2.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot3.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot4.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot5.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot6.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/cultist_archer/headshot7.png");

	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion0.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion1.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion2.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion3.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion4.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion5.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion6.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion7.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/cultist_archer/explosion8.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK]->AddTexture(L"../SharedResource/Texture/cultist_archer/zizizik.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC]->AddTexture(L"../SharedResource/Texture/cultist_archer/damaged.png");
}
