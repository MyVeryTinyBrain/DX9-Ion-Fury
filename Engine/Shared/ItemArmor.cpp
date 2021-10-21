#include "shared_stdafx.h"
#include "ItemArmor.h"
#include "Player.h"

wstring ItemArmor::InitTextureLocalPath() const
{
	return L"../SharedResource/Texture/item/armor_item.png";
}

void ItemArmor::OnTrigger(Player* player)
{
	player->AddArmor(5);
}
