#pragma once
#include "Item.h"
class ItemCardKey :
    public Item
{
    virtual wstring InitTextureLocalPath() const override;
    virtual void OnTrigger(Player* player, bool& destroy) override;
};

