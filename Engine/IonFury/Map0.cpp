#include "stdafx.h"
#include "Map0.h"
#include "Map1.h"
#include <SoundMgr.h>

void Map0::OnLoad(Scene* beforeScene)
{
    SceneMap::OnLoad(beforeScene);

    SoundMgr::PlayBGM(L"../SharedResource/Sound/music/map0.mp3");
}

wstring Map0::GetMapLocalPath() const
{
    return L"../Data/Total/Map00.txt";
}

Scene* Map0::GetNextScene() const
{
    return new Map1;
}

IClonable* Map0::Clone()
{
    return new Map0;
}
