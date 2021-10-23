#pragma once
#include "Item.h"
class ItemBowAmmo :
    public Item
{
    // Item을(를) 통해 상속됨
    virtual wstring InitTextureLocalPath() const override;
    virtual void OnTrigger(Player* player, bool& destroy) override;
};

