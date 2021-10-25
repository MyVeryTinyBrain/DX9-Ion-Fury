#include "stdafx.h"
#include "Map0.h"
#include "Map1.h"
#include <ObjectGarbageBag.h>
#include <ObjectVent.h>

void Map0::OnLoad(Scene* beforeScene)
{
    SceneMap::OnLoad(beforeScene);

    // For test

    //{
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(1, 0.5f, 1.0f);
    //    obj->AddComponent<ObjectGarbageBag>();
    //}
    //{
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, 0.5f, 1.0f);
    //    obj->AddComponent<ObjectGarbageBag>();
    //}
    //{
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(-1, 0.5f, 1.0f);
    //    obj->AddComponent<ObjectGarbageBag>();
    //}

	{
		auto obj = CreateGameObject();
		obj->transform->position = Vec3(-1, -2.4f, 1.0f);
        obj->transform->scale = Vec3(2, 1, 2);
		obj->AddComponent<ObjectVent>();
	}
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
