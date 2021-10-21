#include "shared_stdafx.h"
#include "WarmechSpriteAnimator.h"
#include "SpriteAnimation.h"

void WarmechSpriteAnimator::Awake()
{
	SpriteAnimator::Awake();

	m_idle[(unsigned int)DIR_WARMECH::FRONT] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_front.png");
	m_idle[(unsigned int)DIR_WARMECH::FRONT]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_front_diagonal.png");
	m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::SIDE] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_side.png");
	m_idle[(unsigned int)DIR_WARMECH::SIDE]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_back_diagonal.png");
	m_idle[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->isLoop = true;

	m_idle[(unsigned int)DIR_WARMECH::BACK] = new SpriteAnimation;
	m_idle[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_idle_back.png");
	m_idle[(unsigned int)DIR_WARMECH::BACK]->isLoop = true;

	m_walk[(unsigned int)DIR_WARMECH::FRONT] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front0.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front1.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front2.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front3.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->interval = 0.2f;
	m_walk[(unsigned int)DIR_WARMECH::FRONT]->isLoop = true;
	
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal0.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal1.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal2.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_front_diagonal3.png");
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->interval = 0.2f;
	m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL]->isLoop = true;
	  
	m_walk[(unsigned int)DIR_WARMECH::SIDE] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side0.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side1.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side2.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_side3.png");
	m_walk[(unsigned int)DIR_WARMECH::SIDE]->interval = 0.2f;
	 
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal0.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal1.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal2.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back_diagonal3.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL]->interval = 0.2f;
	
	m_walk[(unsigned int)DIR_WARMECH::BACK] = new SpriteAnimation;
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back0.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back1.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back2.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_back3.png");
	m_walk[(unsigned int)DIR_WARMECH::BACK]->interval = 0.2f;

	m_walkIdle = new SpriteAnimation;
	m_walkIdle->AddTexture(L"../SharedResource/Texture/warmech/warmech_walk_idle.png");
	m_walkIdle->isLoop = true;

	m_shoot = new SpriteAnimation;
	m_shoot->AddTexture(L"../SharedResource/Texture/warmech/warmech_shot0.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/warmech/warmech_shot1.png");
	m_shoot->AddTexture(L"../SharedResource/Texture/warmech/warmech_shot2.png");
	m_shoot->interval = 0.05f;

	m_missile = new SpriteAnimation;
	m_missile->AddTexture(L"../SharedResource/Texture/warmech/warmech_missile0.png");
	m_missile->AddTexture(L"../SharedResource/Texture/warmech/warmech_missile1.png");
	m_missile->AddTexture(L"../SharedResource/Texture/warmech/warmech_missile2.png");
	m_missile->interval = 0.1f;

	m_bullet = new SpriteAnimation;
	m_bullet->AddTexture(L"../SharedResource/Texture/wermech_weapon/Warmechbullet.png");
	m_bullet->isLoop = true;

	m_missileBullet = new SpriteAnimation;
	m_missileBullet->AddTexture(L"../SharedResource/Texture/wermech_weapon/warmechMissile.png");
	m_missileBullet->isLoop = true;

	m_damage = new SpriteAnimation;
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/0.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/1.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/2.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/3.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/4.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/5.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/6.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/7.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/8.png");
	m_damage->AddTexture(L"../SharedResource/Texture/wamech_Hit/9.png");
	m_damage->interval = 0.05f;
	m_damage->isLoop = true;

	m_explosion = new SpriteAnimation;
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/0.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/1.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/2.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/3.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/4.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/5.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/6.png");	
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/7.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/8.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/9.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/10.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/11.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/12.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/13.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/14.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/15.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/16.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/17.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/18.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/19.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/20.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/21.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/22.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/23.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/24.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/25.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/26.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/27.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/28.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/29.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/30.png");
	m_explosion->AddTexture(L"../SharedResource/Texture/warmech_explosion/31.png");
	m_explosion->interval = 0.08f;
	

	SetDefaultAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT]);
}

void WarmechSpriteAnimator::LateUpdate()
{
	SpriteAnimator::LateUpdate();

	if (IsPlayingWalk())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::FRONT])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 2)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::SIDE])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::SIDE], false, true);
			}

			ChangeUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 3)
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::BACK_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}
		else
		{
			if (currentAnimation != m_walk[(unsigned int)DIR_WARMECH::BACK])
			{
				PlayAnimation(m_walk[(unsigned int)DIR_WARMECH::BACK], false, true);
			}

			ResetUVDirection();
		}
	}
	if (IsPlayingIdle())
	{
		if (Abs(m_angle) < 22.5f + 45 * 0)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_WARMECH::FRONT])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT], false, true);
			}

			ResetUVDirection();
		}
		else if (Abs(m_angle) < 22.5f + 45 * 1)
		{
			if (currentAnimation != m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL])
			{
				PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT_DIAGONAL], false, true);
			}

			ChangeUVDirection();
		}


	}

}

void WarmechSpriteAnimator::OnDestroy()
{
	SpriteAnimator::OnDestroy();

	for(int i = 0; i < (int)DIR_WARMECH::MAX; ++i)
		SafeDelete(m_idle[i]);

	for (int i = 0; i < (int)DIR_WARMECH::MAX; ++i)
		SafeDelete(m_walk[i]);

	SafeDelete(m_walkIdle);

	SafeDelete(m_shoot);

	SafeDelete(m_missile);

	SafeDelete(m_bullet);

	SafeDelete(m_missileBullet);

	SafeDelete(m_damage);

	SafeDelete(m_explosion);
}

void WarmechSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{

}

void WarmechSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WarmechSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void WarmechSpriteAnimator::SetAngle(float angle)
{
	m_angle = angle;
}

void WarmechSpriteAnimator::PlayIdle()
{
	if (IsPlayingIdle())
	{
		return;
	}
	PlayAnimation(m_idle[(unsigned int)DIR_WARMECH::FRONT]);
}

void WarmechSpriteAnimator::PlayWalk()
{
	if (IsPlayingWalk())
	{
		return;
	}
	PlayAnimation(m_walk [(unsigned int)DIR_WARMECH::FRONT] );
}

void WarmechSpriteAnimator::PlayWalkIdle()
{
	PlayAnimation(m_walkIdle, true);
}

void WarmechSpriteAnimator::PlayShoot()
{
	PlayAnimation(m_shoot, true);
}

void WarmechSpriteAnimator::PlayMissile()
{
	PlayAnimation(m_missile, true);
}

void WarmechSpriteAnimator::PlayBullet()
{
	PlayAnimation(m_bullet, true);
}

void WarmechSpriteAnimator::PlayMissileBullet()
{
	PlayAnimation(m_missileBullet, true);
}

void WarmechSpriteAnimator::PlayDamage()
{
	PlayAnimation(m_damage, true);
}

void WarmechSpriteAnimator::PlayExplosion()
{
	PlayAnimation(m_explosion, true);
}

bool WarmechSpriteAnimator::IsPlayingIdle() const
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

bool WarmechSpriteAnimator::IsPlayingWalk() const
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

bool WarmechSpriteAnimator::IsPlayingWalkIdle() const
{
	return currentAnimation == m_walkIdle;
}

bool WarmechSpriteAnimator::IsPlayingShoot() const
{
	return currentAnimation == m_shoot;
}

bool WarmechSpriteAnimator::IsPlayingMissile() const
{
	return currentAnimation == m_missile;
}

bool WarmechSpriteAnimator::IsPlayingBullet() const
{
	return currentAnimation == m_bullet;
}

bool WarmechSpriteAnimator::IsPlayingMissileBullet() const
{
	return currentAnimation == m_missileBullet;
}

bool WarmechSpriteAnimator::IsPlayingDamage() const
{
	return currentAnimation == m_damage;
}

bool WarmechSpriteAnimator::IsPlayingExplosion() const
{
	return currentAnimation == m_explosion;
}

SpriteAnimation* WarmechSpriteAnimator::GetSpriteAnimation(SPRITE_WARMECH Spritetype) const
{
	switch (Spritetype)
	{
	case SPRITE_WARMECH::Idle:
		return m_idle[(unsigned int)DIR_WARMECH::FRONT];
	case SPRITE_WARMECH::Walk:
		return m_walk[(unsigned int)DIR_WARMECH::FRONT];
	case SPRITE_WARMECH::WalkIdle:
		return m_walkIdle;
	case SPRITE_WARMECH::Shoot:
		return m_shoot;
	case SPRITE_WARMECH::Missile:
		return m_missile;
	case SPRITE_WARMECH::Bullet:
		return m_bullet;
	case SPRITE_WARMECH::MissileBullet:
		return m_missileBullet;
	case SPRITE_WARMECH::Damage:
		return m_damage;
	case SPRITE_WARMECH::Explosion:
		return m_explosion;
	default:
		return m_idle[(unsigned int)DIR_WARMECH::FRONT];
	}
}
void WarmechSpriteAnimator::ChangeUVDirection()
{
	float direction = m_angle > 0 ? -1.0f : +1.0f;
	GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void WarmechSpriteAnimator::ResetUVDirection()
{
	GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
