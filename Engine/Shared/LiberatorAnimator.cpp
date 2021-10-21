#include "shared_stdafx.h"
#include "LiberatorAnimator.h"
#include "SpriteAnimation.h"

void LiberatorAnimator::InitAnimations()
{
	m_idle[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/liberator/idle_front.png");

	m_idle[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/idle_front_diagonal.png");

	m_idle[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/liberator/idle_side.png");

	m_idle[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/idle_back_diagonal.png");

	m_idle[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/liberator/idle_back.png");

	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/liberator/walk_front0.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/liberator/walk_front1.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/liberator/walk_front2.png");
	m_walk[(unsigned int)DIR::FRONT]->AddTexture(L"../SharedResource/Texture/liberator/walk_front3.png");

	m_walk[(unsigned int)DIR::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_front_diagonal0.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_front_diagonal1.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_front_diagonal2.png");
	m_walk[(unsigned int)DIR::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_front_diagonal3.png");

	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/liberator/walk_side0.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/liberator/walk_side1.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/liberator/walk_side2.png");
	m_walk[(unsigned int)DIR::SIDE]->AddTexture(L"../SharedResource/Texture/liberator/walk_side3.png");

	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/liberator/walk_back_diagonal3.png");

	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/liberator/walk_back0.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/liberator/walk_back1.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/liberator/walk_back2.png");
	m_walk[(unsigned int)DIR::BACK]->AddTexture(L"../SharedResource/Texture/liberator/walk_back3.png");

	m_shoot->AddTexture(L"../SharedResource/Texture/liberator/fire0.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/liberator/fire1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/liberator/fire2.png");

	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/liberator/bodyshot0.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/liberator/bodyshot1.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/liberator/bodyshot2.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/liberator/bodyshot3.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/liberator/bodyshot4.png");
	m_die[(unsigned int)DIE::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/liberator/bodyshot5.png");

	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/liberator/headshot0.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/liberator/headshot1.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/liberator/headshot2.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/liberator/headshot3.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/liberator/headshot4.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/liberator/headshot5.png");
	m_die[(unsigned int)DIE::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/liberator/headshot6.png");

	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion0.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion1.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion2.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion3.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion4.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion5.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion6.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion7.png");
	m_die[(unsigned int)DIE::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/liberator/explosion8.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_ZIZIZIK]->AddTexture(L"../SharedResource/Texture/liberator/zizizik.png");

	m_damage[(unsigned int)DAMAGE::DAMAGE_GENERIC]->AddTexture(L"../SharedResource/Texture/liberator/damaged.png");
}
