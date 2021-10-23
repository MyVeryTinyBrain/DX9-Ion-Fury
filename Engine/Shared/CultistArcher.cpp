#include "shared_stdafx.h"
#include "CultistArcher.h"
#include "CultistArcherAnimator.h"
#include "Player.h"
#include "Arrow.h"

GunnerBaseAnimator* CultistArcher::InitAnimator(GameObject* rendererObject)
{
    return rendererObject->AddComponent<CultistArcherAnimator>();
}

unsigned int CultistArcher::GetAttackCount()
{
    return 1;
}

float CultistArcher::GetDamagedRevengeAttackWaitTime()
{
    return 0.0f;
}

float CultistArcher::GetBreakTime()
{
    return 0.35f;
}

float CultistArcher::GetAttackWaitTime()
{
    return 1.0f;
}

void CultistArcher::ShootToPlayer()
{
    Vec3 playerCoord;
    if (IsPlayerInSite(playerCoord))
    {
        const Vec3& playerPos = Player::GetInstance()->transform->position;
        const Vec3& monsterPos = transform->position;

        Vec3 monsterToPlayer = playerPos - monsterPos;
        monsterToPlayer.Normalize();

        GameObject* arrowObj = CreateGameObject();
        arrowObj->transform->position = transform->position;
        arrowObj->transform->forward = monsterToPlayer;

        Arrow* arrow = arrowObj->AddComponent<Arrow>();
        arrow->rigidbody->velocity = arrow->transform->forward * 50;
        arrow->SetTargetToPlayer();
    }
}
