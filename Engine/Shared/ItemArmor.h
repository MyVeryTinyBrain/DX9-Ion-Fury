#pragma once
#include "Item.h"
class ItemArmor :
    public Item
{
    // Item��(��) ���� ��ӵ�
    virtual wstring InitTextureLocalPath() const override;
    virtual void OnTrigger(Player* player) override;
};

