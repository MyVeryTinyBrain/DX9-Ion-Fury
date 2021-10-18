#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "Gunner.h"
#include "Spider.h"
#include "Skybox.h"
#include "LightLoad.h"
#include "MapLoad.h"
#include "ItemHealthPack.h"
#include "ItemBowAmmo.h"
#include "ItemChaingunAmmo.h"
#include "ItemLauncherAmmo.h"
#include "ItemRevolverAmmo.h"
#include "ItemShotgunAmmo.h"
#include "ItemSMGAmmo.h"
#include "ObjectStair.h"
#include "Cube.h"

IClonable* TestScene::Clone()
{
    return new TestScene;
}

void TestScene::OnLoad(Scene* beforeScene)
{
    //LightLoad::LightObjectLoadJson(L"../Data/TestLight.txt");
    //MapLoad::LoadMap(L"../Data/Map/TestMapData.txt");

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

    {
        auto obj = CreateGameObject();
        obj->AddComponent<Cube>();
    }

    {   // Create directional light
        auto obj = CreateGameObject();

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

        obj->transform->position = Vec3(0, 5, 0);
        obj->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
        auto light = obj->AddComponent<DirectionalLight>();
        light->ambientFactor = 0.6f;
    }

    {
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, -1, 3);
        obj->AddComponent<ObjectStair>();
    }

    {
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(5, 5, 0);
            obj->AddComponent<ItemHealthPack>();
        }
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(5, 5, 1);
            obj->AddComponent<ItemBowAmmo>();
        }
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(5, 5, 2);
            obj->AddComponent<ItemChaingunAmmo>();
        }
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(5, 5, 3);
            obj->AddComponent<ItemLauncherAmmo>();
        }
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(5, 5, 4);
            obj->AddComponent<ItemRevolverAmmo>();
        }
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(5, 5, 5);
            obj->AddComponent<ItemShotgunAmmo>();
        }
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(5, 5, 6);
            obj->AddComponent<ItemSMGAmmo>();
        }
    }

    {   // Create test player
        auto obj = CreateGameObject();
        auto controller = obj->AddComponent<Player>();
    }

    {   // Create ground
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, -3, 0);
        obj->transform->scale = Vec3(100, 1, 100);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    {   // Create obstacle
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, -2, -3);
        obj->transform->scale = Vec3(15, 1, 1);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    {   // Create triangle
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(10, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 0);
        obj->transform->scale = Vec3(20, 10, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<RightTriangleCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    {   // Create rotated ground
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, 0, 10);
        obj->transform->eulerAngle = Vec3(-20, 0, 0);
        obj->transform->scale = Vec3(30, 1, 30);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    {   // Create wall
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(-15, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 90);
        obj->transform->scale = Vec3(40, 1, 40);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    {   // Create wall
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(+15, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 90);
        obj->transform->scale = Vec3(40, 1, 40);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    {   // Create wall
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, 0, -15);
        obj->transform->eulerAngle = Vec3(0, 90, 90);
        obj->transform->scale = Vec3(40, 1, 40);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    {   // Create wall
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, 0, +15);
        obj->transform->eulerAngle = Vec3(0, 90, 90);
        obj->transform->scale = Vec3(40, 1, 40);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;

        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
        collider->restitution = 1.0f;
    }

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(i * 2, 2, j * 2) + Vec3(-10, 0, -10);
            obj->transform->eulerAngle = Vec3(0, 90, 0);
            obj->AddComponent<Gunner>();
        }
    }
}

void TestScene::OnUnload(Scene* nextScene)
{
}
