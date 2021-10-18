#include "stdafx.h"
#include "ItemRevolverAmmo.h"
#include "Player.h"

wstring ItemRevolverAmmo::InitTextureLocalPath() const
{
    return L"../SharedResource/Texture/item/ammo_revolver.png";
}

void ItemRevolverAmmo::OnTrigger(Player* player)
{
    player->AddAmmo(WeaponTypes::Revolver, AmmoTypes::Revolver, 6);
}
