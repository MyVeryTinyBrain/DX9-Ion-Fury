#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "Gunner.h"
#include "Spider.h"
#include "LightLoad.h"

IClonable* TestScene::Clone()
{
    return new TestScene;
}

void TestScene::OnLoad(Scene* beforeScene)
{
    {   // Create directional light
        auto obj = CreateGameObject();

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));

        //obj->transform->position = Vec3(0, 5, 0);
        //obj->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
        //auto light = obj->AddComponent<DirectionalLight>();
        //light->ambientFactor = 0.6f;
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

    //조명 추가 테스트
    {
        auto ltobj = CreateGameObject();
        auto lightcomponet = ltobj->AddComponent<LightLoad>();
        lightcomponet->LightObjectLoad(L"../Data/123333.dat");
    }

    //for (int i = 0; i < 5; ++i)
    //{
    //    for (int j = 0; j < 5; ++j)
    //    {
    //        auto obj = CreateGameObject();
    //        obj->transform->position = Vec3(i * 2, 2, j * 2) + Vec3(-10, 0, -10);
    //        obj->transform->eulerAngle = Vec3(0, 90, 0);
    //        obj->AddComponent<Gunner>();
    //    }
    //}

    /*
    {   // Monster example
        auto obj = CreateGameObject();

        {
            auto renderObj = CreateGameObjectToChild(obj->transform);
            renderObj->transform->scale = Vec3::one() * 3.0f;
            renderObj->transform->localPosition = Vec3(0, 0.5f, 0);

            auto renderer = renderObj->AddComponent<UserMeshBillboardRenderer>();
            renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
            renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/gunner/gunner_fire2.png"));
            renderer->material = Resource::FindAs<Material>(BuiltInAlphaTestMaterial);
            renderer->freezeX = true;
            renderer->freezeZ = true;
        }

        auto body = obj->AddComponent<Rigidbody>();
        body->SetRotationLockAxis(PhysicsAxis::All, true);
        body->mass = 1000;

        {
            auto colObj = CreateGameObjectToChild(obj->transform);

            auto renderer = colObj->AddComponent<UserMeshRenderer>();
            renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInCapsuleUserMesh);
            renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/transparent.png"));
            renderer->material = Resource::FindAs<Material>(BuiltInNolightTransparentMaterial);

            auto collider = colObj->AddComponent<CapsuleCollider>();
        }

        obj->transform->position = Vec3(0, 2, -5);
    }
    */
}

void TestScene::OnUnload(Scene* nextScene)
{
}
