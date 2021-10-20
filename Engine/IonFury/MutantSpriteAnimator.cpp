#include "stdafx.h"
#include "MutantSpriteAnimator.h"
#include "SpriteAnimation.h"

void MutantSpriteAnimator::Awake()
{
    SpriteAnimator::Awake();

    m_create = new SpriteAnimation;
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create0.png");
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create1.png");
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create2.png");
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create3.png");
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create4.png");
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create5.png");
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create6.png");
    m_create->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Create7.png");
    m_create->interval = 0.3f;

    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT] = new SpriteAnimation;
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_headshot0.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_headshot1.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_headshot2.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_headshot3.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_headshot4.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_headshot5.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_headshot6.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_HEADSHOT]->interval = 0.1f;


    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT] = new SpriteAnimation;
    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_bodyshot0.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_bodyshot1.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_bodyshot2.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_bodyshot3.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_bodyshot4.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_bodyshot5.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_BODYSHOT]->interval = 0.1f;

    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION] = new SpriteAnimation;
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion0.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion1.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion2.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion3.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion4.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion5.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion6.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion7.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_explosion8.png");
    m_die[(unsigned int)DIE_MUTANT::DIE_EXPLOSION]->interval = 0.1f;
    
    m_walk = new SpriteAnimation;
    m_walk->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_walk_front0.png");
    m_walk->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_walk_front1.png");
    m_walk->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_walk_front2.png");
    m_walk->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_walk_front3.png");
    m_walk->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_walk_front4.png");
    m_walk->interval = 0.1f;
    m_walk->isLoop = true;

    m_shoot = new SpriteAnimation;
    m_shoot->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Shoot0.png");
    m_shoot->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Shoot1.png");
    m_shoot->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Shoot0.png");
    m_shoot->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Shoot1.png");
    m_shoot->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Shoot0.png");
    m_shoot->AddTexture(L"../SharedResource/Texture/Mutant/Mutant_Shoot1.png");
    m_shoot->interval = 0.1f;

    m_MutantPoison = new SpriteAnimation;
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot0.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot1.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot2.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot3.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot4.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot5.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot6.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot7.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot8.png");
    m_MutantPoison->AddTexture(L"../SharedResource/Texture/Mutant/shoot9.png");
    m_MutantPoison->interval = 0.1f;

    SetDefaultAnimation(m_walk);
}

void MutantSpriteAnimator::LateUpdate()
{

    SpriteAnimator::LateUpdate();
}

void MutantSpriteAnimator::OnDestroy()
{
    SpriteAnimator::OnDestroy();

    SafeDelete(m_create);

    SafeDelete(m_walk);

    SafeDelete(m_shoot);

    SafeDelete(m_MutantPoison);


    for (int i = 0; i < (int)DIE_MUTANT::MAX; ++i)
    {
        SafeDelete(m_die[i]);
    }

}

void MutantSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
    for (int i = 0; i < (int)DIE_MUTANT::MAX; ++i)
    {
        if (current == m_die[i])
        {
            SetDefaultAnimation(nullptr);
            OnDeadAnimated();
        }
    }
}

void MutantSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void MutantSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void MutantSpriteAnimator::SetAngle(float angle)
{
    m_angle = angle;
}

void MutantSpriteAnimator::PlayCreate()
{
    PlayAnimation(m_create, true);
    ResetUVDirection();

    SetDefaultAnimation(m_walk);
}

void MutantSpriteAnimator::PlayWalk()
{
    PlayAnimation(m_walk, true);
    ResetUVDirection();


}

void MutantSpriteAnimator::PlayShoot()
{
    PlayAnimation(m_shoot, true);
    ResetUVDirection();
}

void MutantSpriteAnimator::PlayMutantPoison()
{
    PlayAnimation(m_MutantPoison, true);
    ResetUVDirection();
}

void MutantSpriteAnimator::PlayDie(DIE_MUTANT type)
{
    PlayAnimation(m_die[unsigned int(type)]);
    ResetUVDirection();
}

bool MutantSpriteAnimator::IsPlayingWalk() const
{
    return currentAnimation == m_walk;
}

bool MutantSpriteAnimator::IsPlayingShoot() const
{
    return currentAnimation == m_shoot;
}

bool MutantSpriteAnimator::IsPlayingMutantPoison() const
{
    return currentAnimation == m_MutantPoison;
}

bool MutantSpriteAnimator::IsPlayingDie() const
{
    for (auto die : m_die)
    {
        if (currentAnimation == die)
        {
            return true;
        }
    }
    return false;
}

bool MutantSpriteAnimator::IsPlayingCreate() const
{
    return currentAnimation == m_create;
}

SpriteAnimation* MutantSpriteAnimator::GetDie(DIE_MUTANT type) const
{
    return m_die[(unsigned int)type];
}

SpriteAnimation* MutantSpriteAnimator::GetWalk() const
{
    return m_walk;
}

SpriteAnimation* MutantSpriteAnimator::GetCreate() const
{
    return m_create;
}

SpriteAnimation* MutantSpriteAnimator::GetMutantPoison() const
{
    return m_MutantPoison;
}

void MutantSpriteAnimator::ChangeUVDirection()
{
    float direction = m_angle > 0 ? -1.0f : +1.0f;
    GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void MutantSpriteAnimator::ResetUVDirection()
{
    GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
