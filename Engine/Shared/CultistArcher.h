#pragma once
#include "GunnerBase.h"
class CultistArcher :
    public GunnerBase
{
    OverrideComponentFunction(Update);

    // GunnerBase��(��) ���� ��ӵ�
    virtual GunnerBaseAnimator* InitAnimator(GameObject* rendererObject) override;
    virtual unsigned int GetAttackCount() override;
    virtual float GetDamagedRevengeAttackWaitTime() override;
    virtual float GetBreakTime() override;
    virtual float GetAttackWaitTime() override;
    virtual void ShootToPlayer() override;
};

