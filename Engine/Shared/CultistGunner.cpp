#include "shared_stdafx.h"
#include "CultistGunner.h"
#include "CultistGunnerAnimator.h"
#include "Player.h"
#include "SoundMgr.h"

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

    wchar_t buffer[256];
    swprintf_s(buffer, L"../SharedResource/Sound/gunner/fire/gun/%d.ogg", g_gunSoundIndex++);
    if (g_gunSoundIndex >= GUN_SOUND_MAX)
    {
        g_gunSoundIndex = 0;
    }

    SoundMgr::Play(buffer, CHANNELID::GUNNER_GUN_FIRE1);
    SoundMgr::SetVolume(0.5f, CHANNELID::GUNNER_GUN_FIRE1);
}
