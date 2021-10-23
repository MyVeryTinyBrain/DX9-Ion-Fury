#include "shared_stdafx.h"
#include "ItemSMGAmmo.h"
#include "Player.h"

wstring ItemSMGAmmo::InitTextureLocalPath() const
{
    return L"../SharedResource/Texture/item/ammo_smg.png";
}

void ItemSMGAmmo::OnTrigger(Player* player, bool& destroy)
{
    player->AddAmmo(WeaponTypes::SMG, AmmoTypes::SMG, 20);
}
