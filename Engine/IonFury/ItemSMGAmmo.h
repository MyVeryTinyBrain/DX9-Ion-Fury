#pragma once
#include "Item.h"
class ItemSMGAmmo :
    public Item
{
    // Item을(를) 통해 상속됨
    virtual wstring InitTextureLocalPath() const override;
    virtual void OnTrigger(Player* player) override;
};

