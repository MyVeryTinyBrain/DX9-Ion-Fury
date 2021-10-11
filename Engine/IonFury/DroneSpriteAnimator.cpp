#include "stdafx.h"
#include "DroneSpriteAnimator.h"
#include "SpriteAnimation.h"


void DroneSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(unsigned int)DIR_DRONE::FRONT] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_DRONE::FRONT]->AddTexture(L"../SharedResource/Texture/Drone/Drone_idle_front.png");
	m_idle[(unsigned int)DIR_DRONE::FRONT]->isLoop = true;

	m_idle[(unsigned int)DIR_DRONE::FRONT_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_idle_front_diagonal.png");
	m_idle[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR_DRONE::SIDE] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_DRONE::SIDE]->AddTexture(L"../SharedResource/Texture/Drone/Drone_idle_side.png");
	m_idle[(unsigned int)DIR_DRONE::SIDE]->isLoop = true;

	m_idle[(unsigned int)DIR_DRONE::BACK_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_idle_back_diagonal.png");
	m_idle[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR_DRONE::BACK] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_DRONE::BACK]->AddTexture(L"../SharedResource/Texture/Drone/Drone_idle_back.png");
	m_idle[(unsigned int)DIR_DRONE::BACK]->isLoop = true;

	m_shoot[(unsigned int)DIR_DRONE::FRONT] = new SpriteAnimation;
	m_shoot[(unsigned int)DIR_DRONE::FRONT]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_front0.png");
	m_shoot[(unsigned int)DIR_DRONE::FRONT]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_front1.png");
	m_shoot[(unsigned int)DIR_DRONE::FRONT]->interval = 0.1f;
	m_shoot[(unsigned int)DIR_DRONE::FRONT]->isLoop = true;
	
	m_shoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL] = new SpriteAnimation;
	m_shoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_front_diagonal0.png");
	m_shoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_front_diagonal1.png");
	m_shoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->interval = 0.1f;
	m_shoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->isLoop = true;
	 
	m_shoot[(unsigned int)DIR_DRONE::SIDE] = new SpriteAnimation;
	m_shoot[(unsigned int)DIR_DRONE::SIDE]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_side0.png");
	m_shoot[(unsigned int)DIR_DRONE::SIDE]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_side1.png");
	m_shoot[(unsigned int)DIR_DRONE::SIDE]->interval = 0.1f;
	m_shoot[(unsigned int)DIR_DRONE::SIDE]->isLoop = true;
	
	m_shoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL] = new SpriteAnimation;
	m_shoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_back_diagonal0.png");
	m_shoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_back_diagonal1.png");
	m_shoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->interval = 0.1f;
	m_shoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->isLoop = true;
	
	m_shoot[(unsigned int)DIR_DRONE::BACK] = new SpriteAnimation;
	m_shoot[(unsigned int)DIR_DRONE::BACK]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_back0.png");
	m_shoot[(unsigned int)DIR_DRONE::BACK]->AddTexture(L"../SharedResource/Texture/Drone/Drone_shoot_back1.png");
	m_shoot[(unsigned int)DIR_DRONE::BACK]->interval = 0.1f;
	m_shoot[(unsigned int)DIR_DRONE::BACK]->isLoop = true;

	m_move[(unsigned int)DIR_DRONE::FRONT] = new SpriteAnimation;
	m_move[(unsigned int)DIR_DRONE::FRONT]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_back.png");
	m_move[(unsigned int)DIR_DRONE::FRONT]->isLoop = true;
	
	m_move[(unsigned int)DIR_DRONE::FRONT_DIAGONAL] = new SpriteAnimation;
	m_move[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_front_diagonal.png");
	m_move[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->isLoop = true;
	 
	m_move[(unsigned int)DIR_DRONE::SIDE] = new SpriteAnimation;
	m_move[(unsigned int)DIR_DRONE::SIDE]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_side.png");
	m_move[(unsigned int)DIR_DRONE::SIDE]->isLoop = true;
	
	m_move[(unsigned int)DIR_DRONE::BACK_DIAGONAL] = new SpriteAnimation;
	m_move[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_back_diagonal.png");
	m_move[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->isLoop = true;
	 
	m_move[(unsigned int)DIR_DRONE::BACK] = new SpriteAnimation;
	m_move[(unsigned int)DIR_DRONE::BACK]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_back.png");
	m_move[(unsigned int)DIR_DRONE::BACK]->isLoop = true;

	m_moveShoot[(unsigned int)DIR_DRONE::FRONT] = new SpriteAnimation;
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_front0.png");
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_front1.png");
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT]->interval = 0.1f;
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT]->isLoop = true;
	
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL] = new SpriteAnimation;
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_front_diagonal0.png");
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_front_diagonal1.png");
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->interval = 0.1f;
	m_moveShoot[(unsigned int)DIR_DRONE::FRONT_DIAGONAL]->isLoop = true;
	  
	m_moveShoot[(unsigned int)DIR_DRONE::SIDE] = new SpriteAnimation;
	m_moveShoot[(unsigned int)DIR_DRONE::SIDE]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_side0.png");
	m_moveShoot[(unsigned int)DIR_DRONE::SIDE]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_side1.png");
	m_moveShoot[(unsigned int)DIR_DRONE::SIDE]->interval = 0.1f;
	m_moveShoot[(unsigned int)DIR_DRONE::SIDE]->isLoop = true;
	 
	m_moveShoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL] = new SpriteAnimation;
	m_moveShoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_back_diagonal0.png");
	m_moveShoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_back_diagonal1.png");
	m_moveShoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->interval = 0.1f;
	m_moveShoot[(unsigned int)DIR_DRONE::BACK_DIAGONAL]->isLoop = true;
	  
	m_moveShoot[(unsigned int)DIR_DRONE::BACK] = new SpriteAnimation;
	m_moveShoot[(unsigned int)DIR_DRONE::BACK]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_back0.png");
	m_moveShoot[(unsigned int)DIR_DRONE::BACK]->AddTexture(L"../SharedResource/Texture/Drone/Drone_move_shoot_back1.png");
	m_moveShoot[(unsigned int)DIR_DRONE::BACK]->interval = 0.1f;
	m_moveShoot[(unsigned int)DIR_DRONE::BACK]->isLoop = true;
}

void DroneSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

}

void DroneSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

}

void DroneSpriteAnimator::OnAnimationEnd()
{
}

void DroneSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void DroneSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}
