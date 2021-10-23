#include "shared_stdafx.h"
#include "ItemBowAmmo.h"
#include "Player.h"

wstring ItemBowAmmo::InitTextureLocalPath() const
{
    return L"../SharedResource/Texture/item/ammo_arrow.png";
}

void ItemBowAmmo::OnTrigger(Player* player)
{
    player->AddAmmo(WeaponTypes::Bow, AmmoTypes::Arrow, 5);
}
