#include "shared_stdafx.h"
#include "BasicMutantSpriteAnimator.h"
#include "SpriteAnimation.h"

void BasicMutantSpriteAnimator::Awake()
{
    SpriteAnimator::Awake();

    m_create = new SpriteAnimation;
    m_create->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Create0.png");
    m_create->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Create1.png");
    m_create->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Create2.png");
    m_create->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Create3.png");
    m_create->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Create4.png");
    m_create->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Create5.png");
    m_create->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Create6.png");
    m_create->interval = 0.3f;

    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT] = new SpriteAnimation;
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_HeadShot0.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_HeadShot1.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_HeadShot2.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_HeadShot3.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_HeadShot4.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_HeadShot5.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_HeadShot6.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_HEADSHOT]->interval = 0.1f;

    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION] = new SpriteAnimation;
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion0.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion1.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion2.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion3.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion4.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion5.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion6.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion7.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_explosion8.png");
    m_die[(unsigned int)DIE_BasicMutant::DIE_EXPLOSION]->interval = 0.1f;
    
    m_walk = new SpriteAnimation;
    m_walk->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Walk0.png");
    m_walk->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Walk1.png");
    m_walk->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Walk2.png");
    m_walk->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Walk3.png");
    m_walk->interval = 0.2f;
    m_walk->isLoop = true;

    m_Attack = new SpriteAnimation;
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack0.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack1.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack2.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack3.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack4.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack5.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack6.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack7.png");
    m_Attack->AddTexture(L"../SharedResource/Texture/BasicMutant/BasicMutant_Attack8.png");
    m_Attack->interval = 0.1f;
    m_Attack->isLoop = true;

    SetDefaultAnimation(m_walk);
}

void BasicMutantSpriteAnimator::LateUpdate()
{

    SpriteAnimator::LateUpdate();
}

void BasicMutantSpriteAnimator::OnDestroy()
{
    SpriteAnimator::OnDestroy();

    SafeDelete(m_create);

    SafeDelete(m_walk);

    SafeDelete(m_Attack);


    for (int i = 0; i < (int)DIE_BasicMutant::MAX; ++i)
    {
        SafeDelete(m_die[i]);
    }

}

void BasicMutantSpriteAnimator::OnAnimationEnd(const SpriteAnimation* current)
{
    for (int i = 0; i < (int)DIE_BasicMutant::MAX; ++i)
    {
        if (currentAnimation == m_die[i])
        {
           // SetDefaultAnimation(nullptr);
            SetTransitionMode(false);
            //OnDeadAnimated();
        }
    }

}

void BasicMutantSpriteAnimator::OnAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void BasicMutantSpriteAnimator::OnDefaultAnimationChange(const SpriteAnimation* current, SpriteAnimation** next)
{
}

void BasicMutantSpriteAnimator::SetAngle(float angle)
{
    m_angle = angle;
}

void BasicMutantSpriteAnimator::PlayCreate()
{
    PlayAnimation(m_create, true);
    ResetUVDirection();

    SetDefaultAnimation(m_walk);
}

void BasicMutantSpriteAnimator::PlayWalk()
{
    PlayAnimation(m_walk, true);
    ResetUVDirection();


}

void BasicMutantSpriteAnimator::PlayAttack()
{
    PlayAnimation(m_Attack, true);
    ResetUVDirection();
}


void BasicMutantSpriteAnimator::PlayDie(DIE_BasicMutant type)
{
    PlayAnimation(m_die[unsigned int(type)]);
    ResetUVDirection();
}

bool BasicMutantSpriteAnimator::IsPlayingWalk() const
{
    return currentAnimation == m_walk;
}

bool BasicMutantSpriteAnimator::IsPlayingAttack() const
{
    return currentAnimation == m_Attack;
}


bool BasicMutantSpriteAnimator::IsPlayingDie() const
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

bool BasicMutantSpriteAnimator::IsPlayingCreate() const
{
    return currentAnimation == m_create;
}

SpriteAnimation* BasicMutantSpriteAnimator::GetDie(DIE_BasicMutant type) const
{
    return m_die[(unsigned int)type];
}

SpriteAnimation* BasicMutantSpriteAnimator::GetWalk() const
{
    return m_walk;
}

SpriteAnimation* BasicMutantSpriteAnimator::GetCreate() const
{
    return m_create;
}



void BasicMutantSpriteAnimator::ChangeUVDirection()
{
    float direction = m_angle > 0 ? -1.0f : +1.0f;
    GetRenderer()->userMesh->uvScale = Vec2(direction, 1.0f);
}

void BasicMutantSpriteAnimator::ResetUVDirection()
{
    GetRenderer()->userMesh->uvScale = Vec2(1.0f, 1.0f);
}
