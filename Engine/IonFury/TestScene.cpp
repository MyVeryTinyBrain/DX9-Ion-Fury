#include "stdafx.h"
#include "TestScene.h"
#include "FPSCharacterController.h"

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

        obj->transform->position = Vec3(0, 5, 0);
        obj->transform->forward = Quat::FromEuler(25, 0, 45) * Vec3::down();
        auto light = obj->AddComponent<DirectionalLight>();
        light->ambientFactor = 0.5f;
    }

    {   // Create quad for render texture
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(2, -1.5f, 0);
    }

    {   // Create test player
        auto obj = CreateGameObject();
        auto controller = obj->AddComponent<FPSCharacterController>();
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
    }

    {   // Create triangle
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(10, 0, 0);
        obj->transform->eulerAngle = Vec3(0, 0, 0);
        obj->transform->scale = Vec3(20, 20, 20);

        auto renderer = obj->AddComponent<UserMeshRenderer>();
        renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInRightTriangleUserMesh);
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
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
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
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
        renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/Dev.png"));
        auto body = obj->AddComponent<Rigidbody>();
        body->isKinematic = true;
        auto collider = obj->AddComponent<BoxCollider>();
    }

    // Create transparent objects
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            auto obj = CreateGameObject();
            obj->transform->position = Vec3(float(i), 0, float(j));

            auto renderer = obj->AddComponent<UserMeshRenderer>();
            renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInSphereUserMesh);
            renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/DevAlpha.png"));
            renderer->material = Resource::FindAs<Material>(BuiltInTransparentMaterial);
        }
    }

    {   // Create Orthographic projection camera
        auto obj = CreateGameObject();
        obj->transform->position = Vec3(-1000, -1000, -10);

        auto camChild = CreateGameObjectToChild(obj->transform);
        camChild->transform->localPosition = Vec3(0, 0, +10);

        auto camera = obj->AddComponent<Camera>();
        camera->cameraOrder = 10000;
        camera->overlapMode = true;
        camera->allowRenderLayers = (1 << 5);
        camera->projectionMode = ProjectionMode::Orthographic;

        {   // Create quat for Orthographic projection camera
            auto quadObj = CreateGameObjectToChild(camChild->transform);
            quadObj->transform->localPosition = Vec2(0, 0);
            quadObj->transform->scale = Vec3::one();

            auto renderer = quadObj->AddComponent<UserMeshRenderer>();
            renderer->userMesh = Resource::FindAs<UserMesh>(BuiltInQuadUserMesh);
            renderer->SetTexture(0, Resource::FindAs<Texture>(L"../SharedResource/Texture/revolver/revolver0.png"));
            renderer->material = Resource::FindAs<Material>(BuiltInOverlayMaterial);
            renderer->renderLayerIndex = 5;
        }
    }
}

void TestScene::OnUnload(Scene* nextScene)
{
}
