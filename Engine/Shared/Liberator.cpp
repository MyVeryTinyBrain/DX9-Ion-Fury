#include "shared_stdafx.h"
#include "Liberator.h"
#include "LiberatorAnimator.h"
#include "Player.h"

GunnerBaseAnimator* Liberator::InitAnimator(GameObject* rendererObject)
{
    return rendererObject->AddComponent<LiberatorAnimator>();
}

unsigned int Liberator::GetAttackCount()
{
    return 5;
}

float Liberator::GetDamagedRevengeAttackWaitTime()
{
    return 0.0f;
}

float Liberator::GetBreakTime()
{
    return 0.35f;
}

float Liberator::GetAttackWaitTime()
{
    return 0.5f;
}

void Liberator::ShootToPlayer()
{
    Vec3 playerCoord;
    if (IsPlayerInSite(playerCoord))
    {
        Player::GetInstance()->TakeDamage(1);
    }
}
