#include "stdafx.h"
#include "DroneSpriteAnimator.h"
#include "SpriteAnimation.h"
#include "Player.h"

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

	SetDefaultAnimation(m_idle[(unsigned int)DIR_DRONE::FRONT]);
}

void DroneSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (IsPlayingIdle())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_DRONE::FRONT])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_DRONE::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_DRONE::FRONT_DIAGONAL])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_DRONE::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_DRONE::SIDE])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_DRONE::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_DRONE::BACK_DIAGONAL])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_DRONE::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_DRONE::BACK])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_DRONE::BACK], false, true);
			}

			ResetUVDirection();
		}
	}
	else if (IsPlayingMove())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DRONE::FRONT])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DRONE::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DRONE::FRONT_DIAGONAL])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DRONE::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DRONE::SIDE])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DRONE::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DRONE::BACK_DIAGONAL])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DRONE::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_move[(unsigned int)DIR_DRONE::BACK])
			{
				PlayAnimation(m_move[(unsigned int)DIR_DRONE::BACK], false, true);
			}

			ResetUVDirection();
		}
	}
}
void DroneSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for (int i = 0; i < (int)DIR_DRONE::MAX; ++i)
		SafeDelete(m_idle[i]);

	for (int i = 0; i < (int)DIR_DRONE::MAX; ++i)
		SafeDelete(m_shoot[i]);

	for (int i = 0; i < (int)DIR_DRONE::MAX; ++i)
		SafeDelete(m_move[i]);

	for (int i = 0; i < (int)DIR_DRONE::MAX; ++i)
		SafeDelete(m_moveShoot[i]);
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

void DroneSpriteAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void DroneSpriteAnimator::PlayIdle()
{
	if (IsPlayingIdle())
	{
		return;
	}
	PlayAnimation(m_idle[(unsigned int)DIR_DRONE::FRONT]);
}

void DroneSpriteAnimator::PlayShoot()
{
	if (IsPlayingShoot())
	{
		return;
	}
	PlayAnimation(m_shoot[(unsigned int)DIR_DRONE::FRONT]);
}

void DroneSpriteAnimator::PlayMove()
{
	if (IsPlayingMove())
	{
		return;
	}
	PlayAnimation(m_move[(unsigned int)DIR_DRONE::FRONT]);
}

void DroneSpriteAnimator::PlayMoveShoot()
{
	if (IsPlayingMoveShoot())
	{
		return;
	}
	PlayAnimation(m_moveShoot[(unsigned int)DIR_DRONE::FRONT]);
}

bool DroneSpriteAnimator::IsPlayingIdle() const
{
	for (auto idle : m_idle)
	{
		if (currentAnimation == idle)
		{
			return true;
		}
	}
	return false;
}

bool DroneSpriteAnimator::IsPlayingShoot() const
{
	for (auto shoot : m_shoot)
	{
		if (currentAnimation == shoot)
		{
			return true;
		}
	}
	return false;
}

bool DroneSpriteAnimator::IsPlayingMove() const
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

bool DroneSpriteAnimator::IsPlayingMoveShoot() const
{
	for (auto moveShoot : m_moveShoot)
	{
		if (currentAnimation == moveShoot)
		{
			return true;
		}
	}
	return false;
}

void DroneSpriteAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void DroneSpriteAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
