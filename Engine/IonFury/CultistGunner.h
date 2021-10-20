#pragma once
#include "GunnerBase.h"
class CultistGunner :
    public GunnerBase
{
    // GunnerBase을(를) 통해 상속됨
    virtual GunnerBaseAnimator* InitAnimator(GameObject* rendererObject) override;
    virtual unsigned int GetAttackCount() override;
    virtual float GetDamagedRevengeAttackWaitTime() override;
    virtual float GetBreakTime() override;
    virtual float GetAttackWaitTime() override;
    virtual void ShootToPlayer() override;
};

