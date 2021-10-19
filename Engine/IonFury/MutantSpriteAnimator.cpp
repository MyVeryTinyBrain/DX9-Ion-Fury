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
    m_create->interval = 0.1f;

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




    SetDefaultAnimation(m_create);
}

void MutantSpriteAnimator::LateUpdate()
{
    SpriteAnimator::LateUpdate();
}

void MutantSpriteAnimator::OnDestroy()
{
    SpriteAnimator::OnDestroy();

    for (int i = 0; i < (int)DIE_MUTANT::MAX; ++i)
        SafeDelete(m_die[i]);


    SafeDelete(m_create);

    SafeDelete(m_walk);
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
}

void MutantSpriteAnimator::PlayWalk()
{
    PlayAnimation(m_walk, true);
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
    return m_die[(unsigned int)DIE_MUTANT::MAX];
}

SpriteAnimation* MutantSpriteAnimator::GetWalk() const
{
    return m_walk;
}

SpriteAnimation* MutantSpriteAnimator::GetCreate() const
{
    return m_create;
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
