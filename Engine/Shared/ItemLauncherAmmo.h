#pragma once
#include "Item.h"
class ItemLauncherAmmo :
    public Item
{
    // Item��(��) ���� ��ӵ�
    virtual wstring InitTextureLocalPath() const override;
    virtual void OnTrigger(Player* player, bool& destroy) override;
};

