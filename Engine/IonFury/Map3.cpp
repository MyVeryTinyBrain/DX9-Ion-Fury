#include "stdafx.h"
#include "Map3.h"
#include <SoundMgr.h>

void Map3::OnLoad(Scene* beforeScene)
{
	SceneMap::OnLoad(beforeScene);

	SoundMgr::PlayBGM(L"../SharedResource/Sound/music/map3.mp3");
}

wstring Map3::GetMapLocalPath() const
{
	return L"../Data/Total/Map11.txt";
}

Scene* Map3::GetNextScene() const
{
	return nullptr;
}

IClonable* Map3::Clone()
{
	return new Map3;
}
