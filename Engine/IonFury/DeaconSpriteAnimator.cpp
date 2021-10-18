#include "stdafx.h"
#include "DeaconSpriteAnimator.h"
#include "SpriteAnimation.h"

void DeaconSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_move[(unsigned int)DIR_DECACONE::FRONT] = new SpriteAnimation;
	m_move[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_front0.png");				//앞만 보고있는거 
	m_move[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_front1.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_front2.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_front3.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_front4.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT]->interval = 0.15f; //시간간격
	m_move[(unsigned int)DIR_DECACONE::FRONT]->isLoop = true;

	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL] = new SpriteAnimation;
	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_diagona0.png");	//앞 - 대각선 보고있는거 
	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_diagona1.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_diagona2.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_diagona3.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_diagona4.png");
	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL]->interval = 0.15f; //시간간격
	m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL]->isLoop = true;

	m_move[(unsigned int)DIR_DECACONE::SIDE] = new SpriteAnimation;																	//사이드 
	m_move[(unsigned int)DIR_DECACONE::SIDE]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_side0.png");				
	m_move[(unsigned int)DIR_DECACONE::SIDE]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_side1.png");
	m_move[(unsigned int)DIR_DECACONE::SIDE]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_side2.png");
	m_move[(unsigned int)DIR_DECACONE::SIDE]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_side3.png");
	m_move[(unsigned int)DIR_DECACONE::SIDE]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_move_side4.png");
	m_move[(unsigned int)DIR_DECACONE::SIDE]->interval = 0.15f; //시간간격
	m_move[(unsigned int)DIR_DECACONE::SIDE]->isLoop = true;

	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL] = new SpriteAnimation;																	//사이드 뒤
	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back_diagona0.png");
	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back_diagona1.png");
	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back_diagona2.png");
	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back_diagona3.png");
	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back_diagona4.png");
	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL]->interval = 0.15f; //시간간격
	m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL]->isLoop = true;

	m_move[(unsigned int)DIR_DECACONE::BACK] = new SpriteAnimation;																	//뒤
	m_move[(unsigned int)DIR_DECACONE::BACK]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back0.png");
	m_move[(unsigned int)DIR_DECACONE::BACK]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back1.png");
	m_move[(unsigned int)DIR_DECACONE::BACK]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back2.png");
	m_move[(unsigned int)DIR_DECACONE::BACK]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back3.png");
	m_move[(unsigned int)DIR_DECACONE::BACK]->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_back4.png");
	m_move[(unsigned int)DIR_DECACONE::BACK]->interval = 0.15f; //시간간격
	m_move[(unsigned int)DIR_DECACONE::BACK]->isLoop = true;

	m_Attack = new SpriteAnimation;																//공격
	m_Attack->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack0.png");
	m_Attack->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack1.png");
	m_Attack->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack2.png");
	m_Attack->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Attack3.png");
	m_Attack->interval = 0.1f; //시간간격
	m_Attack->isLoop = true;

	m_dead = new SpriteAnimation;
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead0.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead1.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead2.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead3.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead4.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead5.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead6.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead7.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead8.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead9.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead10.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead11.png");
	m_dead->AddTexture(L"../SharedResource/Texture/Deacon/Deacon_Dead12.png");
	m_dead->interval = 0.1f; //시간간격


	m_flyeffect = new SpriteAnimation;
	m_flyeffect->AddTexture(L"../SharedResource/Texture/Deacon/Effect/fly0.png");
	m_flyeffect->AddTexture(L"../SharedResource/Texture/Deacon/Effect/fly1.png");
	m_flyeffect->AddTexture(L"../SharedResource/Texture/Deacon/Effect/fly2.png");
	m_flyeffect->AddTexture(L"../SharedResource/Texture/Deacon/Effect/fly3.png");
	m_flyeffect->AddTexture(L"../SharedResource/Texture/Deacon/Effect/fly4.png");
	m_flyeffect->interval = 0.1f;
	m_flyeffect->isLoop = true;


	SetDefaultAnimation(m_move[(unsigned int)DIR_DECACONE::FRONT]); //디폴트 애니메이션
	//SetDefaultAnimation(m_Attack); //디폴트 애니메이션
}

void DeaconSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (IsPlayingMove())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DECACONE::FRONT])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DECACONE::FRONT], false, true);
			}

			//ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DECACONE::FRONT_DIAGONAL], false, true);
			}

			//ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DECACONE::SIDE])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DECACONE::SIDE], false, true);
			}

			//ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DECACONE::BACK_DIAGONAL], false, true);
			}

			//ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DECACONE::BACK])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DECACONE::BACK], false, true);
			}

			//ResetUVDirection();
		}
	}
}

void DeaconSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for (int i = 0; i < (int)DIR_DECACONE::MAX; ++i)
	{
		SafeDelete(m_move[i]);
	}

	SafeDelete(m_Attack);

	SafeDelete(m_dead);

	SafeDelete(m_flyeffect);

}

void DeaconSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	for (int i = 0; i < (int)DIE::MAX; ++i)
	{
		if (current == m_dead)
		{
			SetDefaultAnimation(nullptr);
			OnDeadAnimated();
		}
	}
}

void DeaconSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void DeaconSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void DeaconSpriteAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void DeaconSpriteAnimator::PlayMove(DIR_DECACONE edir)
{
	if (IsPlayingMove())
	{
		return;
	}
	PlayAnimation(m_move[(unsigned int)DIR_DECACONE::FRONT]);
}

void DeaconSpriteAnimator::PlayShoot()
{
	if (IsPlayingShoot())
	{
		return;
	}
	PlayAnimation(m_Attack);
}


void DeaconSpriteAnimator::PlayExplosion()
{
	PlayAnimation(m_dead, true);
}

void DeaconSpriteAnimator::PlayDie()
{
	PlayAnimation(m_dead, true);
	ResetUVDirection();
}

void DeaconSpriteAnimator::PlaySmoke()
{
	PlayAnimation(m_flyeffect, true);
	ResetUVDirection();
}

bool DeaconSpriteAnimator::IsPlayingMove() const
{
	for (auto move : m_move)
	{
		if (currentAnimation == move)
		{
			return true;
		}
	}
	return false;
}

bool DeaconSpriteAnimator::IsPlayingShoot() const
{
	return currentAnimation == m_Attack;
}

bool DeaconSpriteAnimator::IsPlayingExplosion() const
{
	return currentAnimation == m_dead;
}

bool DeaconSpriteAnimator::IsPlayingSmoke() const
{
	return currentAnimation == m_flyeffect;
}


SpriteAnimation* DeaconSpriteAnimator::GetMove() const
{
	return m_move[(unsigned int)DIR_DECACONE::FRONT];
}

SpriteAnimation* DeaconSpriteAnimator::GetShoot() const
{
	return m_Attack;
}

SpriteAnimation* DeaconSpriteAnimator::GetExplosion() const
{
	return nullptr;
}

SpriteAnimation* DeaconSpriteAnimator::GetSmoke() const
{
	return  m_flyeffect;
}

void DeaconSpriteAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void DeaconSpriteAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
