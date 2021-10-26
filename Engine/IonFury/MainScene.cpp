#include "stdafx.h"
#include "MainScene.h"
#include "MainSceneComponent.h"

IClonable* MainScene::Clone()
{
    return new MainScene;
}

void MainScene::OnLoad(Scene* beforeScene)
{
    auto obj = CreateGameObject();
    obj->AddComponent<MainSceneComponent>();
}

void MainScene::OnUnload(Scene* nextScene)
{
}
