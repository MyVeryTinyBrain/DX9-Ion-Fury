#include "shared_stdafx.h"
#include "ItemChaingunAmmo.h"
#include "Player.h"

wstring ItemChaingunAmmo::InitTextureLocalPath() const
{
    return L"../SharedResource/Texture/item/ammo_chaingun.png";
}

void ItemChaingunAmmo::OnTrigger(Player* player, bool& destroy)
{
    player->AddAmmo(WeaponTypes::Chaingun, AmmoTypes::Chaingun, 50);
}
