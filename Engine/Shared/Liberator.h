#pragma once
#include "GunnerBase.h"
class Liberator :
    public GunnerBase
{
    virtual GunnerBaseAnimator* InitAnimator(GameObject* rendererObject) override;
    virtual unsigned int GetAttackCount() override;
    virtual float GetDamagedRevengeAttackWaitTime() override;
    virtual float GetBreakTime() override;
    virtual float GetAttackWaitTime() override;
    virtual void ShootToPlayer() override;
};

