#include "stdafx.h"
#include "Map1.h"

wstring Map1::GetMapLocalPath() const
{
    return L"../Data/Total/Map11.txt";
}

Scene* Map1::GetNextScene() const
{
    return nullptr;
}

IClonable* Map1::Clone()
{
    return new Map1;
}
