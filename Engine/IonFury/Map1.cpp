#include "stdafx.h"
#include "Map1.h"
#include "Map2.h"
#include <SoundMgr.h>

void Map1::OnLoad(Scene* beforeScene)
{
    SceneMap::OnLoad(beforeScene);

    SoundMgr::PlayBGM(L"../SharedResource/Sound/music/map3.mp3");
}

wstring Map1::GetMapLocalPath() const
{
    return L"../Data/Total/jihyunmap.txt";
}

Scene* Map1::GetNextScene() const
{
    return new Map2;
}

IClonable* Map1::Clone()
{
    return new Map1;
}
