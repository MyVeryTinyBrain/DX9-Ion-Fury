#pragma once
#include "Item.h"
class ItemChaingunAmmo :
    public Item
{
    // Item��(��) ���� ��ӵ�
    virtual wstring InitTextureLocalPath() const override;
    virtual void OnTrigger(Player* player) override;
};
