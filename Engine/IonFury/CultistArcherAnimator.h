#pragma once
#include "GunnerBaseAnimator.h"
class CultistArcherAnimator :
    public GunnerBaseAnimator
{
    // GunnerBaseAnimator을(를) 통해 상속됨
    virtual void InitAnimations() override;
};

