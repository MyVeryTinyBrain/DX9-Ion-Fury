#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "Gunner.h"
#include "Spider.h"
#include "LightLoad.h"
#include "Deacon.h"

IClonable* TestScene::Clone()
{
    return new TestScene;
}

void TestScene::OnLoad(Scene* beforeScene)
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(i * 2, -1, j * 2);

            auto renderer = obj->AddComponent<UserMeshRenderer>();
            renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
            renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
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

    {
        //LightLoad::LightObjectLoad(L"../Data/123333.dat");
        LightLoad::LightObjectLoadJson(L"../Data/LightObject.txt");
    }

    {
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, 2, -10);
        obj->AddComponent<Deacon>();
    }
}

void TestScene::OnUnload(Scene* nextScene)
{
}
