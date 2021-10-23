#include "shared_stdafx.h"
#include "CultistGunner.h"
#include "CultistGunnerAnimator.h"
#include "Player.h"

GunnerBaseAnimator* CultistGunner::InitAnimator(GameObject* rendererObject)
{
    return rendererObject->AddComponent<CultistGunnerAnimator>();
}

unsigned int CultistGunner::GetAttackCount()
{
    return 2;
}

float CultistGunner::GetDamagedRevengeAttackWaitTime()
{
    return 0.35f;
}

float CultistGunner::GetBreakTime()
{
    return 0.35f;
}

float CultistGunner::GetAttackWaitTime()
{
    return 0.5f;
}

void CultistGunner::ShootToPlayer()
{
    Vec3 playerCoord;
    if (IsPlayerInSite(playerCoord))
    {
        Player::GetInstance()->TakeDamage(1);
    }
}
