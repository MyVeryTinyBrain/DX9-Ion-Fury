#include "shared_stdafx.h"
#include "Liberator.h"
#include "LiberatorAnimator.h"
#include "Player.h"
#include "SoundMgr.h"

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
    return 0.35f;
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

    wchar_t buffer[256];
    swprintf_s(buffer, L"../SharedResource/Sound/gunner/fire/gun/%d.ogg", g_gunSoundIndex++);
    if (g_gunSoundIndex >= GUN_SOUND_MAX)
    {
        g_gunSoundIndex = 0;
    }

    SoundMgr::Play(buffer, CHANNELID::GUNNER_GUN_FIRE0);
    SoundMgr::SetVolume(0.5f, CHANNELID::GUNNER_GUN_FIRE0);
}
