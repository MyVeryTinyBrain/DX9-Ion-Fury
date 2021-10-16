#include "stdafx.h"
#include "DeaconSpriteAnimator.h"
#include "SpriteAnimation.h"

void DeaconSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(unsigned int)DIR_DECACONE::FRONT] = new SpriteAnimation;

	m_idle[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Idle_front0.png");
	m_idle[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Idle_front1.png");
	m_idle[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Idle_front2.png");
	m_idle[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Idle_front3.png");
	m_idle[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Idle_front4.png");
	m_idle[(unsigned int)DIR_DECACONE::FRONT]->interval = 0.1f; //시간간격
	m_idle[(unsigned int)DIR_DECACONE::FRONT]->isLoop = true;

	m_Attack[(unsigned int)DIR_DECACONE::FRONT] = new SpriteAnimation;
	m_Attack[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack0.png");
	m_Attack[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack1.png");
	m_Attack[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack2.png");
	m_Attack[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack3.png");



	SetDefaultAnimation(m_idle[(unsigned int)DIR_DECACONE::FRONT]); //디폴트 애니메이션
}

void DeaconSpriteAnimator::LateUpdate()
{
}

void DeaconSpriteAnimator::OnDestroy()
{
}

void DeaconSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
}

void DeaconSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void DeaconSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void DeaconSpriteAnimator::SetAngle(float angle)
{
}

void DeaconSpriteAnimator::PlayIdle()
{
}

void DeaconSpriteAnimator::PlayShoot()
{
}

void DeaconSpriteAnimator::PlayMove(DIR_DECACONE edir)
{
}

void DeaconSpriteAnimator::PlayMove()
{
}

void DeaconSpriteAnimator::PlayMoveShoot()
{
}

void DeaconSpriteAnimator::PlayExplosion()
{
}

void DeaconSpriteAnimator::PlaySmoke()
{
}

bool DeaconSpriteAnimator::IsPlayingIdle() const
{
	return false;
}

bool DeaconSpriteAnimator::IsPlayingShoot() const
{
	return false;
}

bool DeaconSpriteAnimator::IsPlayingMove() const
{
	return false;
}

bool DeaconSpriteAnimator::IsPlayingMoveShoot() const
{
	return false;
}

bool DeaconSpriteAnimator::IsPlayingExplosion() const
{
	return false;
}

bool DeaconSpriteAnimator::IsPlayingSmoke() const
{
	return false;
}

SpriteAnimation* DeaconSpriteAnimator::GetIdle() const
{
	return nullptr;
}

SpriteAnimation* DeaconSpriteAnimator::GetMove() const
{
	return nullptr;
}

SpriteAnimation* DeaconSpriteAnimator::GetShoot() const
{
	return nullptr;
}

SpriteAnimation* DeaconSpriteAnimator::GetExplosion() const
{
	return nullptr;
}

SpriteAnimation* DeaconSpriteAnimator::GetSmoke() const
{
	return nullptr;
}

void DeaconSpriteAnimator::ChangeUVDirection()
{
}

void DeaconSpriteAnimator::ResetUVDirection()
{
}
