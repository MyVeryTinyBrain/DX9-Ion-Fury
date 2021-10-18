#include "stdafx.h"
#include "ItemShotgunAmmo.h"
#include "Player.h"

wstring ItemShotgunAmmo::InitTextureLocalPath() const
{
    return L"../SharedResource/Texture/item/ammo_shotgun.png";
}

void ItemShotgunAmmo::OnTrigger(Player* player)
{
    player->AddAmmo(WeaponTypes::Launcher, AmmoTypes::Shotgun, 6);
}
