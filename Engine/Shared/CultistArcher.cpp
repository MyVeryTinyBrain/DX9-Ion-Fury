#include "shared_stdafx.h"
#include "CultistArcher.h"
#include "CultistArcherAnimator.h"
#include "Player.h"
#include "Arrow.h"
#include "SoundMgr.h"

void CultistArcher::Update()
{
    GunnerBase::Update();
}

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
    return 0.5f;
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

    SoundMgr::Play(L"../SharedResource/Sound/gunner/fire/bow/0.ogg", CHANNELID::GUNNER_BOW_FIRE);
    SoundMgr::SetVolume(0.5f, CHANNELID::GUNNER_BOW_FIRE);
}
