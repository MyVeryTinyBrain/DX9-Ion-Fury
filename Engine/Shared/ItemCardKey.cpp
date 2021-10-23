#include "shared_stdafx.h"
#include "ItemCardKey.h"
#include "Player.h"

wstring ItemCardKey::InitTextureLocalPath() const
{
    return L"../SharedResource/Texture/item/card.png";
}

void ItemCardKey::OnTrigger(Player* player, bool& destroy)
{
    if (player->cardKey)
    {
        destroy = false;
        return;
    }

    player->cardKey = true;
}

