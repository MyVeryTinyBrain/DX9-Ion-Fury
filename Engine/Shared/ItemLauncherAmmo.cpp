#include "shared_stdafx.h"
#include "ItemLauncherAmmo.h"
#include "Player.h"

wstring ItemLauncherAmmo::InitTextureLocalPath() const
{
    return L"../SharedResource/Texture/item/ammo_launcher.png";
}

void ItemLauncherAmmo::OnTrigger(Player* player, bool& destroy)
{
    player->AddAmmo(WeaponTypes::Launcher, AmmoTypes::Launcher, 6);
}
