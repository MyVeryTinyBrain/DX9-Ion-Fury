#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "CultistGunner.h"
#include "CultistArcher.h"
#include "Liberator.h"
#include "Spider.h"
#include "Skybox.h"
#include "TotalLoad.h"
#include "ItemHealthPack.h"
#include "ItemArmor.h"
#include "ItemBowAmmo.h"
#include "ItemChaingunAmmo.h"
#include "ItemLauncherAmmo.h"
#include "ItemRevolverAmmo.h"
#include "ItemShotgunAmmo.h"
#include "ItemSMGAmmo.h"
#include "ObjectStair.h"
#include "Cube.h"
#include "Skull.h"
#include <ObjectRat.h>
#include <ItemCardKey.h>
#include <Trigger.h>
#include <ObjectButton.h>
#include <ObjectCardScreen.h>
#include <ObjectAutoDoor.h>
#include <ObjectManualDoor.h>

IClonable* TestScene::Clone()
{
    return new TestScene;
}

void TestScene::OnLoad(Scene* beforeScene)
{
    TotalLoad::Load(L"../Data/Total/Map00.txt");

    {
        auto skyboxObj = CreateGameObject();
        Skybox* skybox = skyboxObj->AddComponent<Skybox>();

        skybox->SetTopTexture(L"../SharedResource/Texture/skybox_cloudy/top.png");
        skybox->SetLeftTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        skybox->SetRightTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        skybox->SetForwardTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        skybox->SetBackTexture(L"../SharedResource/Texture/skybox_cloudy/side.png");
        skybox->SetBottomTexture(L"../SharedResource/Texture/skybox_cloudy/bottom.png");
    }

    if (Player::GetInstance() == nullptr)
    {   // Create test player
        auto obj = CreateGameObject();
        auto controller = obj->AddComponent<Player>();
        obj->transform->position = Vec3(0, 1, 0);
    }

    if (1)
    {
        auto obj = CreateGameObject();
        auto controller = obj->AddComponent<ObjectRat>();
        obj->transform->position = Vec3(12.8f, 0, 19.5f);
    }

    if (1)
    {
        auto obj = CreateGameObject();
        auto controller = obj->AddComponent<ObjectRat>();
        obj->transform->position = Vec3(6, 0, 24);
    }

    {
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, -0.5f + 0.6f, 3.0f);
        obj->AddComponent<ItemCardKey>();
    }

    {
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, -0.5f + 0.6f, 2.0f);
        obj->AddComponent<ItemArmor>();
    }

    auto doorObj = CreateGameObject();
    doorObj->transform->position = Vec3(0, -0.5f + 0.6f, 4.2f);
    doorObj->transform->scale = Vec3(2.5f, 4.5f, 1);
    auto door = doorObj->AddComponent<ObjectManualDoor>();

    {
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(2, -0.5f, 3.0f);
        obj->transform->localEulerAngle = Vec3(0, -90, 0);
        obj->transform->localScale = Vec3(1, 2, 1);

        auto trigger = obj->AddComponent<Trigger>();
        trigger->SetMethod(TriggerMethod::Button);

        auto button = obj->AddComponent<ObjectButton>();
        trigger->AddSubordinationComponent(button);
        trigger->AddSubordinationComponent(door);
    }

    {
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(2, -0.5f, 0.0f);
        obj->transform->localEulerAngle = Vec3(0, -90, 0);
        obj->transform->localScale = Vec3(1, 2, 1);

        auto trigger = obj->AddComponent<Trigger>();
        trigger->SetMethod(TriggerMethod::CardCheck);

        auto cardScreen = obj->AddComponent<ObjectCardScreen>();
        trigger->AddSubordinationComponent(cardScreen);
        trigger->AddSubordinationComponent(door);
    }

    //{
    //    auto parent = CreateGameObject();
    //    parent->transform->position = Vec3(0, -2, 2);
    //    parent->transform->scale = Vec3(1, 1, 2);
    //    parent->transform->eulerAngle = Vec3(90, 0, 0);

    //    auto child = CreateGameObjectToChild(parent->transform);
    //    auto renderer = child->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
    //}

    //{   // Create directional light
    //    auto obj = CreateGameObject();

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

    //    obj->transform->position = Vec3(0, 5, 0);
    //    obj->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
    //    auto light = obj->AddComponent<DirectionalLight>();
    //    light->ambientFactor = 0.6f;
    //}

    //{
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, 0.5f, 3);
    //    obj->transform->scale = Vec3(5, 5, 1);
    //    obj->AddComponent<ObjectAutoDoor>();
    //}
    //{
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, -1.7f, 4);
    //    obj->transform->scale = Vec3(2, 1, 1);
    //    obj->AddComponent<Cube>();

    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 5, 0);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 5, 1);
    //        obj->AddComponent<ItemBowAmmo>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 5, 2);
    //        obj->AddComponent<ItemChaingunAmmo>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 5, 3);
    //        obj->AddComponent<ItemLauncherAmmo>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 5, 4);
    //        obj->AddComponent<ItemRevolverAmmo>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 5, 5);
    //        obj->AddComponent<ItemShotgunAmmo>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 5, 6);
    //        obj->AddComponent<ItemSMGAmmo>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(0, 0, 9);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(1, 0, 9);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(2, 0, 9);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(3, 0, 9);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(4, 0, 9);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 0, 9);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(6, 0, 9);
    //        obj->AddComponent<ItemHealthPack>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(0, 0, 10);
    //        obj->AddComponent<ItemArmor>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(1, 0, 10);
    //        obj->AddComponent<ItemArmor>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(2, 0, 10);
    //        obj->AddComponent<ItemArmor>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(3, 0, 10);
    //        obj->AddComponent<ItemArmor>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(4, 0, 10);
    //        obj->AddComponent<ItemArmor>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(5, 0, 10);
    //        obj->AddComponent<ItemArmor>();
    //    }
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(6, 0, 10);
    //        obj->AddComponent<ItemArmor>();
    //    }
    //}

    //{   // Create test player
    //    auto obj = CreateGameObject();
    //    auto controller = obj->AddComponent<Player>();
    //}

    //{   // Create ground
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, -3, 0);
    //    obj->transform->scale = Vec3(100, 1, 100);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create obstacle
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, -2, -3);
    //    obj->transform->scale = Vec3(15, 1, 1);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create obstacle
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, -1, -3);
    //    obj->transform->scale = Vec3(7.5f, 1, 1);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create obstacle
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, 1, 8);
    //    obj->transform->scale = Vec3(15, 3, 1);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create triangle
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(10, 0, 0);
    //    obj->transform->eulerAngle = Vec3(0, 0, 0);
    //    obj->transform->scale = Vec3(20, 10, 20);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<RightTriangleCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}


    //{   // Create rotated ground
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, 0, 10);
    //    obj->transform->eulerAngle = Vec3(-20, 0, 0);
    //    obj->transform->scale = Vec3(30, 1, 30);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create wall
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(-15, 0, 0);
    //    obj->transform->eulerAngle = Vec3(0, 0, 90);
    //    obj->transform->scale = Vec3(40, 1, 40);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create wall
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(+15, 0, 0);
    //    obj->transform->eulerAngle = Vec3(0, 0, 90);
    //    obj->transform->scale = Vec3(40, 1, 40);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create wall
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, 0, -15);
    //    obj->transform->eulerAngle = Vec3(0, 90, 90);
    //    obj->transform->scale = Vec3(40, 1, 40);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //{   // Create wall
    //    auto obj = CreateGameObject();
    //    obj->transform->position = Vec3(0, 0, +15);
    //    obj->transform->eulerAngle = Vec3(0, 90, 90);
    //    obj->transform->scale = Vec3(40, 1, 40);

    //    auto renderer = obj->AddComponent<UserMeshRenderer>();
    //    renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
    //    renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
    //    auto body = obj->AddComponent<Rigidbody>();
    //    body->isKinematic = true;

    //    auto collider = obj->AddComponent<BoxCollider>();
    //    collider->friction = 1.0f;
    //    collider->restitution = 1.0f;
    //}

    //for (int i = 0; i < 5; ++i)
    //{
    //    for (int j = 0; j < 5; ++j)
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(i * 4, 2, j * 4) + Vec3(-10, 0, -10);
    //        obj->transform->eulerAngle = Vec3(0, 90, 0);

    //        int r = rand() % 4;

    //        switch (r)
    //        {
    //            case 0:
    //                obj->AddComponent<CultistGunner>();
    //                break;
    //            case 1:
    //                obj->AddComponent<CultistArcher>();
    //                break;
    //            case 2:
    //                obj->AddComponent<Liberator>();
    //                break;
    //        }
    //    }
    //}

  //  {
		//auto obj = CreateGameObject();
  //      obj->transform->position = Vec3(-0, 0, -0);
		//obj->transform->eulerAngle = Vec3(0, 0, 0);
  //      obj->AddComponent<Skull>();
  //  }
}

void TestScene::OnUnload(Scene* nextScene)
{
}
