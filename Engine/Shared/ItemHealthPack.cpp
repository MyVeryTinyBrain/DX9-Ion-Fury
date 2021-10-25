#include "shared_stdafx.h"
#include "ItemHealthPack.h"
#include "Player.h"

wstring ItemHealthPack::InitTextureLocalPath() const
{
	return L"../SharedResource/Texture/item/healthpack.png";
}

void ItemHealthPack::OnTrigger(Player* player, bool& destroy)
{
	if (player->HP >= 100)
	{
		destroy = false;
		return;
	}

	player->AddHP(20);
}
