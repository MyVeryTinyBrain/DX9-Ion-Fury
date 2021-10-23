#include "shared_stdafx.h"
#include "WendigoSpriteAnimator.h"
#include "SpriteAnimation.h"

void WendigoSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle = new SpriteAnimation;
	m_idle->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_idle_foront.png");
	m_idle->isLoop = true;

	m_walk[(unsigned int)DIR_WENDIGO::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WENDIGO::FRONT]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront0.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront1.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront2.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront3.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT]->interval = 0.2f;
	m_walk[(unsigned int)DIR_WENDIGO::FRONT]->isLoop = true;
				
	m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront_diagonal0.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront_diagonal1.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront_diagonal2.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_foront_diagonal3.png");
	m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL]->interval = 0.2f;
	m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL]->isLoop = true;
			
	m_walk[(unsigned int)DIR_WENDIGO::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WENDIGO::SIDE]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_side0.png");
	m_walk[(unsigned int)DIR_WENDIGO::SIDE]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_side1.png");
	m_walk[(unsigned int)DIR_WENDIGO::SIDE]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_side2.png");
	m_walk[(unsigned int)DIR_WENDIGO::SIDE]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_side3.png");
	m_walk[(unsigned int)DIR_WENDIGO::SIDE]->interval = 0.2f;
				
	m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back_diagonal3.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL]->interval = 0.2f;
					
	m_walk[(unsigned int)DIR_WENDIGO::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WENDIGO::BACK]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back0.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back1.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back2.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_walk_back3.png");
	m_walk[(unsigned int)DIR_WENDIGO::BACK]->interval = 0.2f;


	m_attack[(unsigned int)ATTACK_WENDIGO::Swing] = new SpriteAnimation;
	m_attack[(unsigned int)ATTACK_WENDIGO::Swing]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_attack0.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Swing]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_attack1.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Swing]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_attack2.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Swing]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_attack3.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Swing]->interval = 0.1f;


	m_attack[(unsigned int)ATTACK_WENDIGO::Jump] = new SpriteAnimation;
	m_attack[(unsigned int)ATTACK_WENDIGO::Jump]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_jump0.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Jump]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_jump1.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Jump]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_jump2.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Jump]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_jump3.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Jump]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_jump4.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Jump]->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_jump5.png");
	m_attack[(unsigned int)ATTACK_WENDIGO::Jump]->interval = 0.1f;



	m_die = new SpriteAnimation;
	m_die->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_die0.png");
	m_die->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_die1.png");
	m_die->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_die2.png");
	m_die->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_die3.png");
	m_die->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_die4.png");
	m_die->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_die5.png");
	m_die->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_die6.png");
	m_die->interval = 0.1f;


	m_damage = new SpriteAnimation;
	m_damage->AddTexture(L"../SharedResource/Texture/Wendigo/Wendigo_damage.png");
	m_damage->isLoop = true;

	//SetDefaultAnimation(m_walk[(unsigned int)DIR_WENDIGO::FRONT]);
	SetDefaultAnimation(m_idle);
}

void WendigoSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (IsPlayingWalk())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WENDIGO::FRONT])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WENDIGO::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WENDIGO::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WENDIGO::SIDE])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WENDIGO::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WENDIGO::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WENDIGO::BACK])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WENDIGO::BACK], false, true);
			}

			ResetUVDirection();
		}
	}
}

void WendigoSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	SafeDelete(m_idle);

	for (int i = 0; i < (int)DIR_WENDIGO::MAX; ++i)
		SafeDelete(m_walk[i]);

	for (int i = 0; i < (int)ATTACK_WENDIGO::Max; ++i)
		SafeDelete(m_attack[i]);

	SafeDelete(m_damage);

	SafeDelete(m_die);

}

void WendigoSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
	if (currentAnimation == m_die)
		SetTransitionMode(false);
}

void WendigoSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WendigoSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WendigoSpriteAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void WendigoSpriteAnimator::PlayIdle()
{
	PlayAnimation(m_idle, true);
}

void WendigoSpriteAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}
	PlayAnimation(m_walk[(unsigned int)DIR_WENDIGO::FRONT]);
}

void WendigoSpriteAnimator::PlayDamage()
{
	PlayAnimation(m_damage, true);
}

void WendigoSpriteAnimator::PlayAttack(ATTACK_WENDIGO type)
{
	if (IsPlayingAttack())
	{
		return;
	}
	PlayAnimation(m_attack[(unsigned int)type]);
}

void WendigoSpriteAnimator::PlayJump()
{
	PlayAnimation(m_attack[(unsigned int)ATTACK_WENDIGO::Jump], true);
}

void WendigoSpriteAnimator::PlaySwing()
{
	PlayAnimation(m_attack[(unsigned int)ATTACK_WENDIGO::Swing], true);
}
void WendigoSpriteAnimator::PlayDie()
{
	PlayAnimation(m_die, true);
}

bool WendigoSpriteAnimator::IsPlayingIdle() const
{
	return currentAnimation == m_idle;
}

bool WendigoSpriteAnimator::IsPlayingWalk() const
{
	for (auto walk : m_walk)
	{
		if (currentAnimation == walk)
		{
			return true;
		}
	}
	return false;
}

bool WendigoSpriteAnimator::IsPlayingAttack() const
{
	for (auto attack : m_attack)
	{
		if (currentAnimation == attack)
		{
			return true;
		}
	}
	return false;
}

bool WendigoSpriteAnimator::IsPlayingDie() const
{
	return currentAnimation == m_die;
}

bool WendigoSpriteAnimator::IsPlayingDamage() const
{
	return currentAnimation == m_damage;
}

SpriteAnimation* WendigoSpriteAnimator::GetIdle() const
{
	return m_idle;
}

SpriteAnimation* WendigoSpriteAnimator::GetWalk() const
{
	return m_walk[(unsigned int)DIR_WENDIGO::FRONT];
}

SpriteAnimation* WendigoSpriteAnimator::GetAttack(ATTACK_WENDIGO type) const
{
	return m_attack[(unsigned int)type];
}

SpriteAnimation* WendigoSpriteAnimator::GetDie() const
{
	return m_die;
}

SpriteAnimation* WendigoSpriteAnimator::GetDamage() const
{
	return m_damage;
}

void WendigoSpriteAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void WendigoSpriteAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
