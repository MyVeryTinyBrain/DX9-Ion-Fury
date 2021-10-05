#include "stdafx.h"
#include "TestScene.h"
#include "FPSCharacterController.h"

IClonable* TestScene::Clone()
{
    return new TestScene;
}

void TestScene::OnLoad(Scene* beforeScene)
{
    {   // Load textures
        Texture::CreateFromFile(L"../SharedResourced/Texture/Dev.png");
    }

    {   // Create directional light
        auto obj = CreateGameObject();
        obj->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
        auto light = obj->AddComponent<DirectionalLight>();
        light->ambientFactor = 0.2f;
    }

    {   // Create test player
        auto obj = CreateGameObject();
        auto cameraObj = CreateGameObjectToChild(obj->transform);
        cameraObj->AddComponent<FPSCharacterController>();
    }

    {   // Create ground
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, -3, 0);
        obj->transform->scale = Vec3(20, 1, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<BoxCollider>();
        collider->friction = 1.0f;
    }

    {   // Create triangle
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(10, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 0);
        obj->transform->scale = Vec3(20, 20, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<RightTriangleCollider>();
    }

    {   // Create rotated ground
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(0, 0, 10);
        obj->transform->eulerAngle = Vec3(-20, 0, 0);
        obj->transform->scale = Vec3(20, 1, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<BoxCollider>();
    }

    {   // Create wall
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(-10, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 90);
        obj->transform->scale = Vec3(20, 1, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCubeUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResourced/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<BoxCollider>();
    }
}

void TestScene::OnUnload(Scene* nextScene)
{
}
