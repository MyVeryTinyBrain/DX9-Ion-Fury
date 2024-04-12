#include "stdafx.h"
#include "Map2.h"
#include "MainScene.h"
#include <SoundMgr.h>

void Map2::OnLoad(Scene* beforeScene)
{
	SceneMap::OnLoad(beforeScene);

	SoundMgr::PlayBGM(L"../SharedResource/Sound/music/map3.mp3");
}

wstring Map2::GetMapLocalPath() const
{
	return L"../Data/Total/Map11.txt";
}

Scene* Map2::GetNextScene() const
{
	return new MainScene;
}

IClonable* Map2::Clone()
{
	return new Map2;
}
